

class LRUCache{
    private: 
    int capacity;   //determines the size of cache
    int time;       //used for modification of timestamp
    unordered_map<int, RBTree::RBNode*> map; //hashmap to store the nodes
    RBtree* tree; 
    int hits; // Cache hit counter
    int misses; // Cache miss counter
    int evictions; // Eviction counter
    long long totalAccessTime; // Total access time for cache operations

    //function to increase timestamp
    void increaseTimestamp(RBTree::RBNode* node) 
    {
        node->time_stamp = ++time;
    }

     RBTree::RBNode* leftmost() 
     {
        // Traverses the tree to find the leftmost (least recently ised with smallest timestamp) node
        RBTree::RBNode* cur = tree.root;
        while (cur && cur->left != nullptr) {
            cur = cur->left;
        }
        return current;
    }
    public:

    LRUCache(int cap) : capacity(cap), time(0) {} //constructor for lru cache with capacity cap

    //get function
    int get(int key) {

        auto start = high_resolution_clock::now();

        if (map.find(key) == map.end()) {
            return -1; // Key not found
            misses++; // Record cache miss
        }
        RBTree::RBNode* node = map[key]; //find the node with key
        increaseTimestamp(node); // Update the timestamp for the node
        tree.insert(node->key, node->value, node->time_stamp); // Re-insert the node with updated timestamp to update the tree
        hits++; // Record cache hit
        auto end = high_resolution_clock::now();
        totalAccessTime += duration_cast<nanoseconds>(end - start).count();
        return node->value; //return its value
    }
    void put(int key, int value) {

        auto start = high_resolution_clock::now();

        if (map.find(key) != map.end()) {
            // if Key already exists, update its value and timestamp
            RBTree::RBNode* node = map[key]; //find node with key
            node->value = value;    //update it's value
            increaseTimestamp(node); //increase timestamp;
            tree.insert(node->key, node->value, node->time_stamp);
        }
        // if key does not exist already
         else 
         {
            if (map.size() == capacity) {
                // Cache is full, remove the least recently used (leftmost node in RBTree)
                RBTree::RBNode* leastRecent = getLeastRecentNode();
                map.erase(leastRecent->key); //remove from map
                tree.delete(leastRecent->key); //remove from tree
                evictions++; // Record eviction event
            }
            // Insert the new node in the cache and the RBTree
            RBTree::RBNode* newNode = tree.insert(key, value, ++time);
            map[key] = newNode;
        }
        auto end = high_resolution_clock::now();
        totalAccessTime += duration_cast<nanoseconds>(end - start).count();
    }

    double HitRate() const{                     //Measures how often the requested data is found in the cache 
                                                //without requiring a new insertion. This shows how effectively
                                                // the cache is meeting requests.
        return (double)hits / (hits + misses);
        //number of time we find key the data/total number of times we look for the data
    }

    double AverageAccessTime() const{       //Measures the average time taken to retrieve a value from the cache.
                                               // This reflects the speed of cache operations.
        int totalOps = hits + misses;
        return totalOps > 0 ? (double)totalAccessTime / totalOps : 0; 
        //total time/number of ops gives avg access time
    }

    int EvictionCount() const {                //Counts the number of evictions (when the cache removes the least 
                                               //recently used item to make space for new ones). A high eviction 
                                               //count can suggest that the cache size is too small for the workload. 
        return evictions;
    }

}

