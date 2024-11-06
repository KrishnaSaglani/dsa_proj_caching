#include <bits/stdc++.h>
using namespace std;

class LRUCache
{
    //first making a dll
    class node
    {
        public:
        int key;
        int value;
        node* prev;
        node * next;

        node(int k, int v)
        {
            key =k;
            value = v;
        }
    } ;

     node* head= new node(-1,-1);
     node * tail = new node(-1,-1);

     int capacity;
     unordered_map <int, node*> hash;

    LRUCache(int capacity)
    {
        capacity=0;
        head->next = tail;
        head->prev = NULL;
        tail->next = NULL;
        tail->prev = head;
    }

    void add_new_node(int key, int val)
    {
        //add node at the head
            //but you also have to check if it is
            //already present lol

        node* new_n = new node(key, val);
        new_n->next = head->next;
        head->next->prev = new_n;
        head->next = new_n;
        new_n->prev = head;

        //now you gotta add this node to the hashmap
        if(hash.find(key)!= hash.end())
        {
            delete_node(hash[key]);//remove from dll
            hash.erase(key);//remove from hash
        }

        hash[key] = new_n;
    }

    void delete_node(node* add) //deletes node whatever its position
    {
        node* hold = add;
        hold->prev->next = hold->next;
        hold->next->prev = hold->prev;
        free(hold);

        hash.erase(add->key);
        // don't forget to delete from hashmap

    }

    void put(int key, int val)
    {
        if(hash.size() == capacity)
        {
            //delete tail node,then add new node
            delete_node(tail->prev);
            add_new_node(key, val);
        }
        else
        {
            add_new_node(key, val);
        }
    }

    void get(int key)
    {
        if(hash.find(key) == hash.end())
        {
            //key not found
            cout<<"-1"<<endl;
        }
        else //found
        {
            cout<<hash[key]->value<<endl;
            //now I gotta remove this from wherever it is 
            //and put it at start of LRU

            int val = hash[key]->value;
            delete_node(hash[key]);
            add_new_node(key,val);

        }
    }
};


int main()
{
    LRUCache LC(10);
    LC.put(1,5);
    LC.put(2,7);
    LC.get(3);
    LC.get(1);
    LC.put(3,7);
    LC.get(5,9);
    LC.get(10);
}

//random comment
