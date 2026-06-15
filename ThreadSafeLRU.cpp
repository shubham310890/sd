#include <bits/stdc++.h>
using namespace std;

class ThreadSafeLRUCache {
private:
    int capacity;

    // front = most recently used
    // back  = least recently used
    list<pair<int, int>> dll;

    // key -> iterator pointing to node in list
    unordered_map<int, list<pair<int, int>>::iterator> cache;

    // protects both map and list
    mutex mtx;

public:
    ThreadSafeLRUCache(int capacity) {
        this->capacity = capacity;
    }

    int get(int key) {
        lock_guard<mutex> lock(mtx);

        auto it = cache.find(key);

        if (it == cache.end()) {
            return -1;
        }

        // Move accessed node to front
        dll.splice(dll.begin(), dll, it->second);

        return it->second->second;
    }

    void put(int key, int value) {
        lock_guard<mutex> lock(mtx);

        auto it = cache.find(key);

        // Case 1: key already exists
        if (it != cache.end()) {
            it->second->second = value;

            // Move updated node to front
            dll.splice(dll.begin(), dll, it->second);
            return;
        }

        // Case 2: key does not exist and cache is full
        if ((int)dll.size() == capacity) {
            auto lruNode = dll.back();
            int lruKey = lruNode.first;

            dll.pop_back();
            cache.erase(lruKey);
        }

        // Insert new key-value at front
        dll.push_front({key, value});
        cache[key] = dll.begin();
    }
};
