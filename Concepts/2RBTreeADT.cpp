#include <bits/stdc++.h>
using namespace std;

//This shall contain rotation logic as well...so AVL is incorporated into same code




class RBTree
{
    private:
        //node stuct:
        typedef struct RBNode
        {
            int key;
            int value; //dont forget this is actually for an LRU cache
            int time_stamp;
            RBNode* left;
            RBNode* right;
            char colour; //'r' or 'b'

            RBNode(int k, int v, int ts)
            {
                key = k;
                value = v;
                left = NULL; right = NULL;
                colour = 'r';
                time_stamp = ts;
            }
        }RBNode;

        RBNode * root;
    
        RBNode * leftRotate(RBNode * Imb_node)  //Imb_node = Imbalanced node
        {

        }
        //not designed to handle the colors right away
        //this is simply a rotator

        RBNode * rightRotate(RBNode * Imb_node)
        {
            
        }
        //not designed to handle the colors right away
        //this is simply a rotator

        //height() and balance_check() is not required thanks to RB tree properties
        RBNode * insert_helper(RBNode * new_node)
        {
            //STEP 1: normal BST insertion
            //here I am ordering this on the basis of timestamps
        }

    public:
    RBNode  * insert(int key, int val, int time_stamp)
    {
        RBNode * new_node = new RBNode(key, val, time_stamp);
        //note: default colour is red

        if(root == NULL)
        {
            root = new_node;
            new_node->colour = 'b';
        }
        else
        {
            root = insert_helper(new_node);
        }

        return new_node;
        //I will thus be returning the new_node's address so that it can be put into the 
        //hashmap also
        
        //hashmap shall have the key followed by node address
    }

        
};