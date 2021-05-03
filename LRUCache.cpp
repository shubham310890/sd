class DLLNode
{
    public:
    int key;
    int value;
    DLLNode * left;
    DLLNode * right;
    
    DLLNode(int key, int value)
    {
        this->value = value;
        this->key = key;
        this->left = this->right = NULL;
    }
    void setLeft(DLLNode * left)
    {
        this->left = left;
    }
    void setRight(DLLNode * right)
    {
        this->right = right;
    }
    DLLNode* getLeft()
    {
        return this->left;
    }
    DLLNode* getRight()
    {
        return this->right;
    }
    int getValue()
    {
        return this->value;
    }
    
};
class LRUCache {
    int capacity;
    DLLNode * head, *tail;
    map<int, DLLNode *> nodeMap;
    int currSize;
public:
    LRUCache(int capacity) {
        this->capacity = capacity;
        this->head = this->tail = NULL;
        this->currSize = 0;
    }
    
    int get(int key)
    {
        if(nodeMap.find(key) == nodeMap.end())
        {
            return -1;
        }
        else 
        {
            DLLNode* node = nodeMap[key];
            moveToFront(key);
             
            return node->value;
        }
        
       // cout << tail->key << " " << tail->value << endl;
    }
    void moveToFront(int key)
    {
        DLLNode * node = nodeMap[key];
        if(node != head)
        {
            DLLNode * prev = node->left;
            prev->right = node->right;
            if(node->right == NULL) tail = prev;
            else node->right->left = prev;
            node->left = NULL;
            head->left = node;
            node->right=head;
            head = node;
        }
    }
    void removeNode()
    {
        DLLNode * node = tail;
        if(node->left)
        {
            node->left->right = NULL;
            
            tail = node->left;
        } else {
            head = tail = NULL;
        }
        currSize--;
        nodeMap.erase(node->key);
    }
    void addNode(int key, int value)
    {
        DLLNode * node = new DLLNode(key, value);
        if(head == NULL)
        {
            head = tail = node;
        } else {
            node->right = head;
            head->left = node;
            head = node;
        }
        currSize++;
        nodeMap[key] = node;
    }
    void put(int key, int value)
    {
        if(nodeMap.find(key) != nodeMap.end())
        {
            DLLNode * node = nodeMap[key];
            node->value = value;
            moveToFront(key);
        } else {
            if(currSize >= capacity)
            {
                removeNode();
            }
            addNode(key, value);
    }
    }
};
