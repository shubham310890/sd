#include <bits/stdc++.h>
using namespace std;

class TimeMapTTLWithCleanup {
private:
    struct ValueEntry {
        string value;
        int expiryTime;

        ValueEntry() {}

        ValueEntry(const string& val, int exp) {
            value = val;
            expiryTime = exp;
        }
    };

    struct HeapEntry {
        int expiryTime;
        string key;
        int timestamp;

        bool operator>(const HeapEntry& other) const {
            return expiryTime > other.expiryTime;
        }
    };

    unordered_map<string, map<int, ValueEntry>> store;

    priority_queue<HeapEntry, vector<HeapEntry>, greater<HeapEntry>> minHeap;

public:
    void set(string key, string value, int timestamp, int ttl) {
        int expiryTime = timestamp + ttl;

        store[key][timestamp] = ValueEntry(value, expiryTime);

        minHeap.push({expiryTime, key, timestamp});
    }

    string get(string key, int queryTime) {
        if (!store.count(key)) {
            return "";
        }

        auto& versions = store[key];

        auto it = versions.upper_bound(queryTime);

        while (it != versions.begin()) {
            --it;

            if (queryTime < it->second.expiryTime) {
                return it->second.value;
            }

            if (it == versions.begin()) {
                break;
            }
        }

        return "";
    }

    void cleanup(int currentTime) {
        while (!minHeap.empty() && minHeap.top().expiryTime <= currentTime) {
            HeapEntry expired = minHeap.top();
            minHeap.pop();

            const string& key = expired.key;
            int timestamp = expired.timestamp;
            int expiryTime = expired.expiryTime;

            if (!store.count(key)) {
                continue;
            }

            auto& versions = store[key];

            auto it = versions.find(timestamp);

            if (it == versions.end()) {
                continue;
            }

            // Verify heap entry is not stale
            if (it->second.expiryTime == expiryTime) {
                versions.erase(it);
            }

            if (versions.empty()) {
                store.erase(key);
            }
        }
    }
};
