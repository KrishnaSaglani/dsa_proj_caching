#include "0final_tree.h"
#include <chrono>
#include <unordered_map>
using namespace std;

class LRUCache{
    private: 
    int capacity;   //determines the size of cache
    int time;       //used for modification of timestamp
    unordered_map<int, RBNode*> map; //hashmap to store the nodes
    RBTree tree; 
    int hits; // Cache hit counter
    int misses; // Cache miss counter
    int evictions; // Eviction counter
    long long totalAccessTime; // Total access time for cache operations

    //function to increase timestamp
    void increaseTimestamp(RBNode* node) 
    {
        node->time_stamp = ++time;
    }

     RBNode* leftmost() 
     {
        // Traverses the tree to find the leftmost (least recently ised with smallest timestamp) node
        RBNode* cur = tree.root;
        while (cur && cur->left != nullptr) {
            cur = cur->left;
        }
        return cur;
    }
    public:

    LRUCache(int cap) : capacity(cap), time(0) 
    {
        evictions =0;
        hits =0;
        misses =0;
        totalAccessTime =0;

    } //constructor for lru cache with capacity cap

    //get function
    string get(int key) {

        auto start = chrono::high_resolution_clock::now();

        if (map.find(key) == map.end()) {
            misses++; // Record cache miss
            return "not found"; // Key not found
            
        }
        RBNode* node = map[key]; //find the node with key
        string tempo = node->value;
        
        //increaseTimestamp(node); // Update the timestamp for the node
        map.erase(key);
        map[key] = tree.insert(node->key, node->value, ++(node->time_stamp)); // Re-insert the node with updated timestamp to update the tree
        tree.delete_node(node);
        hits++; // Record cache hit
        auto end = chrono::high_resolution_clock::now();
        totalAccessTime += chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        
        return tempo; //return its value
    }

    void put(int key, string value) {

        auto start = chrono::high_resolution_clock::now();

        if (map.find(key) != map.end()) {
            // if Key already exists, update its value and timestamp
            RBNode* node = map[key]; //find node with key
            node->value = value;    //update it's value
            increaseTimestamp(node); //increase timestamp;
            tree.insert(node->key, node->value, node->time_stamp);
        }
        // if key does not exist already
         else 
         {
            if (map.size() == capacity) {
                // Cache is full, remove the least recently used (leftmost node in RBTree)
                RBNode* leastRecent = tree.LRU_node;
                map.erase(leastRecent->key); //remove from map
                tree.delete_node(tree.LRU_node); //remove from tree
                evictions++; // Record eviction event
            }
            // Insert the new node in the cache and the RBTree
            RBNode* newNode = tree.insert(key, value, ++time);
            map[key] = newNode;
        }
        auto end = chrono::high_resolution_clock::now();
        totalAccessTime += chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    }

    double HitRate() const{                     //Measures how often the requested data is found in the cache 
                                                //without requiring a new insertion. This shows how effectively
                                                // the cache is meeting requests.
        return (double)hits / (hits + misses);
        //number of time we find key the data/total number of times we look for the data
    }

    long long AverageAccessTime() const{       //Measures the average time taken to retrieve a value from the cache.
                                               // This reflects the speed of cache operations.
        int totalOps = hits + misses;
        return totalOps > 0 ? (long long)totalAccessTime / totalOps : 0; 
        //total time/number of ops gives avg access time
    }

    int EvictionCount() const {                //Counts the number of evictions (when the cache removes the least 
                                               //recently used item to make space for new ones). A high eviction 
                                               //count can suggest that the cache size is too small for the workload. 
        return evictions;
    }

};

