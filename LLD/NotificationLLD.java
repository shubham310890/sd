import java.time.Duration;
import java.util.List;
import java.util.Objects;

public final class NotificationService {
    private final RecipientResolver recipientResolver;
    private final PreferenceService preferenceService;
    private final ChannelSelector channelSelector;
    private final NotificationRepository repository;
    private final DeduplicationStore deduplicationStore;
    private final DeliveryQueue deliveryQueue;

    public NotificationService(
            RecipientResolver recipientResolver,
            PreferenceService preferenceService,
            ChannelSelector channelSelector,
            NotificationRepository repository,
            DeduplicationStore deduplicationStore,
            DeliveryQueue deliveryQueue
    ) {
        this.recipientResolver = recipientResolver;
        this.preferenceService = preferenceService;
        this.channelSelector = channelSelector;
        this.repository = repository;
        this.deduplicationStore = deduplicationStore;
        this.deliveryQueue = deliveryQueue;
    }

    public void notify(NotificationRequest request) {
        Objects.requireNonNull(request);

        if (request.dedupKey() != null) {
            boolean reserved = deduplicationStore.reserve(
                    request.dedupKey(),
                    Duration.ofMinutes(10)
            );

            if (!reserved) {
                return;
            }
        }

        Notification notification = new Notification(
                request.tenantId(),
                request.eventType(),
                request.actorId(),
                request.priority(),
                request.correlationId()
        );

        repository.saveNotification(notification);

        List<Recipient> recipients = recipientResolver.resolve(request);

        for (Recipient recipient : recipients) {
            NotificationContext context = new NotificationContext(
                    request.tenantId(),
                    request.eventType(),
                    request.actorId(),
                    recipient,
                    request.payload(),
                    request.priority(),
                    request.correlationId()
            );

            List<ChannelType> candidateChannels = channelSelector.selectChannels(context);

            for (ChannelType channelType : candidateChannels) {
                if (!preferenceService.isAllowed(context, channelType)) {
                    continue;
                }

                NotificationDelivery delivery = new NotificationDelivery(
                        notification.id(),
                        request.tenantId(),
                        recipient,
                        channelType
                );

                repository.saveDelivery(delivery);
                deliveryQueue.enqueue(delivery.id());
            }
        }
    }
}

public final class DeliveryWorker {
    private final DeliveryQueue deliveryQueue;
    private final NotificationRepository repository;
    private final TemplateRenderer templateRenderer;
    private final ChannelRegistry channelRegistry;
    private final RetryPolicy retryPolicy;

    public DeliveryWorker(
            DeliveryQueue deliveryQueue,
            NotificationRepository repository,
            TemplateRenderer templateRenderer,
            ChannelRegistry channelRegistry,
            RetryPolicy retryPolicy
    ) {
        this.deliveryQueue = deliveryQueue;
        this.repository = repository;
        this.templateRenderer = templateRenderer;
        this.channelRegistry = channelRegistry;
        this.retryPolicy = retryPolicy;
    }

    public void processNext() {
        String deliveryId = deliveryQueue.poll();
        if (deliveryId == null) {
            return;
        }

        NotificationDelivery delivery = repository.findDeliveryById(deliveryId)
                .orElseThrow(() -> new IllegalStateException("Delivery not found: " + deliveryId));

        delivery.incrementAttempt();
        repository.updateDelivery(delivery);

        NotificationContext context = new NotificationContext(
                delivery.tenantId(),
                "UNKNOWN_EVENT_TYPE", // In production, load parent Notification also.
                null,
                delivery.recipient(),
                java.util.Map.of(),
                Priority.NORMAL,
                null
        );

        RenderedMessage message = templateRenderer.render(context, delivery.channelType());

        DeliveryCommand command = new DeliveryCommand(
                delivery.id(),
                delivery.tenantId(),
                delivery.recipient(),
                delivery.channelType(),
                message,
                null
        );

        NotificationChannel channel = channelRegistry.get(delivery.channelType());
        DeliveryResult result = channel.send(command);

        if (result.isSuccess()) {
            delivery.markDelivered(result.providerMessageId());
        } else if (retryPolicy.shouldRetry(result, delivery.attempt())) {
            delivery.markRetryScheduled(
                    result.failureReason(),
                    retryPolicy.nextRetryAt(delivery.attempt())
            );
            deliveryQueue.enqueue(delivery.id());
        } else {
            delivery.markFailed(result.failureReason());
        }

        repository.updateDelivery(delivery);
    }
}
