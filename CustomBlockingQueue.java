import com.sun.jndi.ldap.Connection;

import java.util.Random;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class CustomBlockingQueue {
    final Lock lock = new ReentrantLock();
    final Condition dataAvailableCondition = lock.newCondition();
    final Condition bufferAvailableCondition = lock.newCondition();

    final int capacity = 6;
    private Object[] arr = new Object[capacity];

    private int count = 0;
    private int getIndex = 0, putIndex = 0;

    public void enqueu(Object o) throws InterruptedException {
        lock.lock();
        while(count == capacity)
        {
            bufferAvailableCondition.await();
        }
        arr[putIndex] = o;
        System.out.println("Producing: "+o);
        count++;
        putIndex++;
        putIndex = putIndex == capacity ? 0 : putIndex;
        dataAvailableCondition.signal();
        lock.unlock();
    }

    public Object deque() throws InterruptedException {
        lock.lock();
        while(count == 0)
        {
            dataAvailableCondition.await();
        }
        Object result = arr[getIndex];
        System.out.println("Consuming: "+result);
        getIndex++;
        count--;
        getIndex = getIndex == capacity ? 0 : getIndex;
        bufferAvailableCondition.signal();
        lock.unlock();
        return result;
    }
};
class Producer implements Runnable
{
    private CustomBlockingQueue blockingQueue;
    public Producer(final CustomBlockingQueue blockingQueue)
    {
        this.blockingQueue = blockingQueue;
    }
    public void run() {
        for(int i = 0; i < 15; i++) {
            try {
                blockingQueue.enqueu(i);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }
}
class Consumer implements Runnable
{
    private CustomBlockingQueue blockingQueue;
    public Consumer(final CustomBlockingQueue blockingQueue)
    {
        this.blockingQueue = blockingQueue;
    }
    public void run() {
        for(int i = 0 ; i < 15; i++) {
            try {
                Object o = blockingQueue.deque();
                //System.out.println("After consuming: " + o);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }
}
class Main
{
    public static void main(String[] args)
    {
        CustomBlockingQueue customBlockingQueue = new CustomBlockingQueue();
        Thread producer = new Thread(new Producer(customBlockingQueue));
        Thread consumer = new Thread(new Consumer(customBlockingQueue));
        producer.start();
        consumer.start();
    }
}
