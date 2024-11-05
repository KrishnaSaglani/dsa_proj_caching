#include <iostream>
#include <unordered_map>
using namespace std;

struct Node
 {
    int key;
    int value;
    int timestamp;
    string color;
    Node* left;
    Node* right;
    Node* parent;

    Node(int k, int v, int t) :key(k), value(v),timestamp(t),color("RED"), left(nullptr), right(nullptr), parent(nullptr) {}
};

class LRUCache {
private:
    int capacity;
    int time;
    Node* root;
    Node* null;
    unordered_map<int, Node*> map;  

    void updateTimestamp(Node* node) {
        node->timestamp = ++time;
       
    }

    Node* leftmost(Node* node) {
        while (node->left != null) node = node->left;
        return node;
    }

    void insert(Node* node) {}

    void delete_(int key) {}


public:
    LRUCache(int cap) : capacity(cap), time(0) {
        null = new Node(0, 0, 0);
        null->color = "BLACK";
        null->left = null->right = null;
        root = null;
    }

    int get(int key) {
        if (map.find(key) == map.end()) return -1;
        Node* node = map[key];
        updateTimestamp(node); 
        delete_(node->key);
        insert(node); 
        return node->value;
    }

    void put(int key, int value) {
        if (map.find(key) != map.end()) {
            Node* node = map[key];
            node->value = value;
            updateTimestamp(node);
        } else {
            if (map.size() == capacity) {
                Node* lruNode = leftmost(root);
                map.erase(lruNode->key);
                deleteNode(lruNode->key);
            }
            Node* newNode = new Node(key, value, ++time);
            map[key] = newNode;
            insertNode(newNode);
        }
    }

    void inorder() {
        inorderHelper(root);
        cout << endl;
    }

    void inorderHelper(Node* node) {
        if (node != null) {
            inorderHelper(node->left);
            cout << "(" << node->key << ", " << node->value << ", " << node->timestamp << ") ";
            inorderHelper(node->right);
        }
    }
};
