#include <bits/stdc++.h>
using namespace std;

class LFUCache {
private:
    struct Node {
        int key;
        int value;
        int freq;

        Node(int k, int v) {
            key = k;
            value = v;
            freq = 1;
        }
    };

    int capacity;
    int minFreq;

    // key -> Node*
    unordered_map<int, Node*> keyNode;

    // key -> iterator in frequency list
    unordered_map<int, list<Node*>::iterator> keyIter;

    // frequency -> list of nodes
    // front = least recently used inside this frequency
    // back  = most recently used inside this frequency
    unordered_map<int, list<Node*>> freqList;

    void increaseFrequency(Node* node) {
        int key = node->key;
        int oldFreq = node->freq;

        // Remove node from old frequency list
        freqList[oldFreq].erase(keyIter[key]);

        // If old frequency list becomes empty
        if (freqList[oldFreq].empty()) {
            freqList.erase(oldFreq);

            // If this was minimum frequency, increase minFreq
            if (minFreq == oldFreq) {
                minFreq++;
            }
        }

        // Increase frequency
        node->freq++;

        int newFreq = node->freq;

        // Add node to back of new frequency list
        // back means most recently used in this frequency
        freqList[newFreq].push_back(node);

        // Update iterator
        auto it = freqList[newFreq].end();
        --it;
        keyIter[key] = it;
    }

public:
    LFUCache(int capacity) {
        this->capacity = capacity;
        this->minFreq = 0;
    }

    int get(int key) {
        if (capacity == 0) {
            return -1;
        }

        if (!keyNode.count(key)) {
            return -1;
        }

        Node* node = keyNode[key];

        increaseFrequency(node);

        return node->value;
    }

    void put(int key, int value) {
        if (capacity == 0) {
            return;
        }

        // Case 1: key already exists
        if (keyNode.count(key)) {
            Node* node = keyNode[key];
            node->value = value;

            increaseFrequency(node);
            return;
        }

        // Case 2: cache is full
        if ((int)keyNode.size() == capacity) {
            // Evict LRU node from minimum frequency list
            Node* nodeToRemove = freqList[minFreq].front();

            int removeKey = nodeToRemove->key;

            freqList[minFreq].pop_front();

            if (freqList[minFreq].empty()) {
                freqList.erase(minFreq);
            }

            keyNode.erase(removeKey);
            keyIter.erase(removeKey);

            delete nodeToRemove;
        }

        // Insert new node with frequency 1
        Node* newNode = new Node(key, value);

        keyNode[key] = newNode;

        freqList[1].push_back(newNode);

        auto it = freqList[1].end();
        --it;
        keyIter[key] = it;

        minFreq = 1;
    }

    ~LFUCache() {
        for (auto& entry : keyNode) {
            delete entry.second;
        }
    }
};
