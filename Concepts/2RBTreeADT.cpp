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
            
            RBNode* parent; //new pointer for us
            char colour; //'r' or 'b'
            

            RBNode(int k, int v, int ts)
            {
                key = k;
                value = v;
                left = NULL; right = NULL;
                parent = NULL;
                colour = 'r';
                time_stamp = ts;
                
            }
        }RBNode;

        RBNode * root;
        void leftRotate(RBNode * Imb_node)  //Imb_node = Imbalanced node
        {
            RBNode * child = Imb_node->right;
            RBNode * temp = child->left;
           
        }
        //not designed to handle the colors right away
        //this is simply a rotator

        void rightRotate(RBNode * Imb_node)
        {
            
        }
        //not designed to handle the colors right away
        //this is simply a rotator

        RBNode * find_sibling(RBNode * child)
        {
            RBNode* parent = child->parent;
            if(parent->left == child ) return parent->right;
            else return parent->left;
        }

        //btw parent always exists...uncle and grandparent may not
        void Balance(RBNode * child, RBNode* parent)
        {
            if(parent->colour == 'b') return; //yay no problem here

            //now else case: parent_>colour == 'r'
            //hence grandparent MUST be black for sure
            RBNode * grandparent = parent->parent;
            if(grandparent == NULL)
            {
                parent->colour = 'b';
                return;
            }

            RBNode * uncle = find_sibling(parent);
            if(uncle==NULL  || uncle->colour == 'b') //black uncle..in RB trees we consider NULL as black also
            {
                //rotation then recolouring
                //assuming grandparent exists..if not then still okay
                bool left_child = (child->time_stamp<=parent->time_stamp)? true:false;


                if(parent->time_stamp<=grandparent->time_stamp) //parent at left
                {
                    if(left_child)
                    {
                        rightRotate(grandparent);
                        grandparent->colour = 'r';
                        parent->colour = 'b';
                    }
                    else
                    {
                        leftRotate(parent);
                        rightRotate(grandparent);
                        grandparent->colour = 'r';
                        child->colour = 'b';
                    }
                }

                else //parent at right
                {
                    if(left_child)
                    {
                        rightRotate(parent);
                        leftRotate(grandparent);
                        grandparent->colour = 'r';
                        child->colour = 'b';
                    }
                    else
                    {
                        leftRotate(grandparent);
                        grandparent->colour = 'r';
                        parent->colour = 'b';
                    }
                }

            }
            else if(uncle->colour == 'r')
            {
                parent->colour = 'b';
                uncle->colour = 'b';
                 //since uncle exists..grandparent must exist too
                grandparent->colour = 'r';
                Balance(grandparent,grandparent->parent);
            }
        }

        //height() and balance_check() is not required thanks to RB tree properties
        RBNode * insert_helper(RBNode * current, RBNode * new_node)
        {
            //STEP 1: normal BST insertion, except the parent thing
            //here I am ordering this on the basis of timestamps

            if(new_node->time_stamp <= current->time_stamp)
            {
                if(current->left == NULL)
                {
                    current->left = new_node;
                    new_node->parent = current;
                }
                else
                {
                    current->left->parent = current;
                    //hence as we go along, the parents are being established also 
                    current->left = insert_helper(current->left,new_node);
                }
                
                //now current point becomes parent
            }
            else if(new_node->time_stamp > current->time_stamp)
            {
                if(current->right == NULL)
                {
                    current->right = new_node;
                    new_node->parent = current;
                }
                else
                {
                    current->right->parent = current;
                    //hence as we go along, the parents are being established also 
                    current->right = insert_helper(current->right,new_node);
                }
            }

            //but wait wait...we are NOT done yet
            //finally, new node inserted at bottom and current is its parent
            //STEP 2: Validate RB Tree properties

            if(new_node->parent == current) //so validation occurs only once
            //balancing only required ONCE in insertion case, but NOT the same for deletion
            {
                Balance(new_node,current);
            }
            
            return current;
        }
        //this function always returns the links to root

    public:
    RBNode * LRU_node; //keep updating this node as we go deleting LRU elements

    RBNode  * insert(int key, int val, int time_stamp)
    {
        RBNode * new_node = new RBNode(key, val, time_stamp);
        //note: default colour is red

        if(root == NULL)
        {
            root = new_node;
            LRU_node = root;
            new_node->colour = 'b'; // root is always black
        }
        else
        {
            root = insert_helper(root,new_node);
        }

        return new_node;
        //I will thus be returning the new_node's address so that it can be put into the 
        //hashmap also
        
        //hashmap shall have the key followed by node address
    }
        
};

