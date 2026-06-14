// Basic 

#include <bits/stdc++.h>
using namespace std;

class InMemoryKVStore {
private:
    unordered_map<string, string> store;

public:
    void put(string key, string value) {
        store[key] = value;
    }

    string get(string key) {
        if (store.find(key) == store.end()) {
            return "NOT_FOUND";
        }

        return store[key];
    }

    bool remove(string key) {
        if (store.find(key) == store.end()) {
            return false;
        }

        store.erase(key);
        return true;
    }
};


// Follow-up 1: Add TTL / Expiry

#include <bits/stdc++.h>
using namespace std;

class InMemoryKVStore {
private:
    struct Entry {
        string value;
        long long expiryTime; // -1 means never expires
    };

    unordered_map<string, Entry> store;

    long long currentTime() {
        return chrono::duration_cast<chrono::seconds>(
            chrono::system_clock::now().time_since_epoch()
        ).count();
    }

    bool isExpired(const Entry& entry) {
        if (entry.expiryTime == -1) {
            return false;
        }

        return currentTime() > entry.expiryTime;
    }

public:
    void put(string key, string value) {
        store[key] = {value, -1};
    }

    void putWithTTL(string key, string value, int ttlSeconds) {
        long long expiry = currentTime() + ttlSeconds;
        store[key] = {value, expiry};
    }

    string get(string key) {
        if (store.find(key) == store.end()) {
            return "NOT_FOUND";
        }

        Entry entry = store[key];

        if (isExpired(entry)) {
            store.erase(key);
            return "NOT_FOUND";
        }

        return entry.value;
    }

    bool remove(string key) {
        if (store.find(key) == store.end()) {
            return false;
        }

        store.erase(key);
        return true;
    }
};

// Follow-up 2: Better TTL Cleanup 

#include <bits/stdc++.h>
using namespace std;

class InMemoryKVStore {
private:
    struct Entry {
        string value;
        long long expiryTime; // -1 means key never expires
    };

    struct ExpiryNode {
        long long expiryTime;
        string key;
    };

    struct Compare {
        bool operator()(const ExpiryNode& a, const ExpiryNode& b) {
            return a.expiryTime > b.expiryTime; 
            // min-heap based on expiryTime
        }
    };

    unordered_map<string, Entry> store;

    priority_queue<
        ExpiryNode,
        vector<ExpiryNode>,
        Compare
    > minHeap;

private:
    long long currentTimeInSeconds() {
        return chrono::duration_cast<chrono::seconds>(
            chrono::system_clock::now().time_since_epoch()
        ).count();
    }

    bool isExpired(long long expiryTime) {
        if (expiryTime == -1) {
            return false;
        }

        return currentTimeInSeconds() >= expiryTime;
    }

    void cleanupExpiredKeys() {
        long long now = currentTimeInSeconds();

        while (!minHeap.empty()) {
            ExpiryNode top = minHeap.top();

            // If earliest expiry is still in future, stop cleanup
            if (top.expiryTime > now) {
                break;
            }

            minHeap.pop();

            string key = top.key;
            long long heapExpiryTime = top.expiryTime;

            // Key may already be deleted
            if (store.find(key) == store.end()) {
                continue;
            }

            Entry currentEntry = store[key];

            // Important stale heap entry check:
            // Same key may have been updated with a new TTL.
            // Old heap entry should not delete the latest value.
            if (currentEntry.expiryTime != heapExpiryTime) {
                continue;
            }

            // If expiry matches and time has passed, delete from store
            store.erase(key);
        }
    }

public:
    void put(string key, string value) {
        cleanupExpiredKeys();

        store[key] = {value, -1};
    }

    void putWithTTL(string key, string value, int ttlSeconds) {
        cleanupExpiredKeys();

        long long expiryTime = currentTimeInSeconds() + ttlSeconds;

        store[key] = {value, expiryTime};

        minHeap.push({expiryTime, key});
    }

    string get(string key) {
        cleanupExpiredKeys();

        if (store.find(key) == store.end()) {
            return "NOT_FOUND";
        }

        Entry entry = store[key];

        if (isExpired(entry.expiryTime)) {
            store.erase(key);
            return "NOT_FOUND";
        }

        return entry.value;
    }

    bool remove(string key) {
        cleanupExpiredKeys();

        if (store.find(key) == store.end()) {
            return false;
        }

        store.erase(key);
        return true;
    }

    bool containsKey(string key) {
        cleanupExpiredKeys();

        return store.find(key) != store.end();
    }

    int size() {
        cleanupExpiredKeys();

        return store.size();
    }

    void printStore() {
        cleanupExpiredKeys();

        cout << "Current Store:" << endl;

        for (auto &entry : store) {
            cout << entry.first << " -> " << entry.second.value;

            if (entry.second.expiryTime == -1) {
                cout << " | no expiry";
            } else {
                cout << " | expires at " << entry.second.expiryTime;
            }

            cout << endl;
        }
    }
};
