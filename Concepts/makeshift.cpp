#include <bits/stdc++.h>
using namespace std;

//This shall contain rotation logic as well...so AVL is incorporated into same code

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


class RBTree
{
    private:

        void leftRotate(RBNode * Imb_node)  //Imb_node = Imbalanced node
        {
            RBNode * child = Imb_node->right;
            RBNode * temp = child->left;
            RBNode * source = Imb_node->parent;

            //now lets rotate
            child->left = Imb_node;
            Imb_node->right = temp; // or temp
            if(temp!=NULL)temp->parent = Imb_node;
            Imb_node->parent = child;
            child->parent = source;

            // //extra precaution due to some errors
            // if(temp == NULL) Imb_node->right = NULL; useless

            //test prints
            if(Imb_node->right == NULL)cout<<"Imb_node linked well with temp"<<endl;
            if(child ->left == Imb_node)cout<<endl<<" new root and Imb linked well too"<<endl;
            if(Imb_node->left == NULL)cout<<"Imb left has stayed NULL";

            cout<<endl<<"in rot"<<endl;
            printLinks(child);
            cout<<"out of rot";
            //concl: we are perfectly ok till here

            //relink to source now
            if(source==NULL) return;
            else
            {
                if(source->time_stamp >= Imb_node->time_stamp)//Imb_Node WAS left child
                {
                    source->left = child;
                }
                else
                {
                    source->right = child;
                }
            }

            
        }
        //not designed to handle the colors right away
        //this is simply a rotator

        void rightRotate(RBNode * Imb_node)
        {
            RBNode * child = Imb_node->left;
            RBNode * temp = child->right;
            RBNode * source = Imb_node->parent;
            

            //now lets rotate
            child->right = Imb_node;
            Imb_node->left = temp;
            if(temp != NULL)temp->parent = Imb_node;
            Imb_node->parent = child;
            child->parent = source;

            //relink to source now
            if(source==NULL) return;
            else
            {
                if(source->time_stamp >= Imb_node->time_stamp)//Imb_Node WAS left child
                {
                    source->left = child;
                }
                else
                {
                    source->right = child;
                }
            }
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
            if(parent == NULL) return; // view uncle-'red' case
            if(parent->colour == 'b') return; //yay no problem here

            //now else case: parent->colour == 'r'
            //hence grandparent MUST be black for sure
            RBNode * grandparent = parent->parent;
            // if you reach here...grandparent MUST exist for sure

            RBNode * uncle = find_sibling(parent);
            if(uncle==NULL)cout<<"Uncle is NULL"<<endl;
            if(uncle==NULL  || uncle->colour == 'b') //black uncle..in RB trees we consider NULL as black also
            {
                //rotation then recolouring
                //assuming grandparent exists..if not then still okay
                //as it will just be a NULL return point
                bool left_child = (child->time_stamp <= parent->time_stamp)? true:false;


                if(parent->time_stamp <= grandparent->time_stamp) //parent at left
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
                        child->colour = 'b';//now child is in place of parent
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
                 if(grandparent -> parent == NULL) //grandparent is the root
                 {
                        grandparent->colour = 'b';
                 }
                 else
                 {
                        grandparent->colour = 'r';
                        Balance(grandparent,grandparent->parent);
                 }
                
            }

            cout<<"in bal"<<endl;
            printLinks(root->parent);
            cout<<"out of bal";

            return;
        }

        //height() and balance_check() is not required thanks to RB tree properties
        void insert_helper(RBNode * current, RBNode * new_node)
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
                    insert_helper(current->left,new_node);
                }
                
                //now current point becomes parent
            }
            else //if(new_node->time_stamp > current->time_stamp)
            {
                if(current->right == NULL)
                {
                    current->right = new_node;
                    new_node->parent = current;
                }
                else
                {
                    current->right->parent = current;//extra precaution
                    //hence as we go along, the parents are being established also 
                    insert_helper(current->right,new_node);
                }
            }

            //but wait wait...we are NOT done yet
            //finally, new node inserted at bottom and current is its parent

            //STEP 2: Validate RB Tree properties

            if(new_node->parent == current) //so validation occurs only once
            //balancing only required ONCE in insertion case, but NOT the same for deletion
            {
                Balance(new_node,current);

                //Now just CLIMB to the top from here and whatever is 
                //the topmost thing..just make it the root

                while(current->parent != NULL) current = current->parent;
                root = current; //SUPER SUPER IMPORTANT step
                //because the tree is rotating around all the time...so root keeps changing

                cout<<endl<<"in hf"<<endl;
                printLinks(current);
                cout<<"out of hf";
            }
        }
        //this function always returns the links to root

        void delete_fixup(RBNode * d_black, RBNode * parent)
        {
            if(parent == NULL) //dbalck is root
            {
                root = parent;
                return;
                //the black height of tree just went up by 1
                // as we converted double black to single without actually adding a black node
            }

            RBNode * sibling = (parent->left == d_black)? parent->right: parent->left;
            bool left_child = (parent->left == d_black)? true : false;

            //Q: what if sibling is NULL?
            if(sibling == NULL)
            {
                delete_fixup(parent, parent->parent);
                return;
                //if sibling is null, then double black is pushed up to parent node
            }

            if(sibling->colour == 'r')
            {
                if(left_child)
                {
                    leftRotate(parent);
                    parent->colour = 'r';
                    sibling->colour = 'b';

                    //now we will have a NEW sibling..whose colour is ALWAYS BLACK
                    //as it was child of a red node
                    //Hence, be go back to case of sibling->colour being black

                    if(parent == root)
                    {
                        root = parent->parent;
                    }

                    delete_fixup(d_black, parent);
                }
                else
                {
                    rightRotate(parent);
                    parent->colour = 'r';
                    sibling->colour = 'b';

                    //root manipulation
                    if(parent == root)
                    {
                        root = parent->parent;
                    }

                    delete_fixup(d_black, parent);
                }
            }
            else //sibling is black
            {
                cout<<"Sibling is "<<sibling->time_stamp<<endl;
                if(sibling->left->colour == 'b' && sibling->right->colour == 'b')
                {
                    //both kids black
                    if(parent->colour == 'r')
                    {
                        parent->colour = 'b';
                        //red + black = double black
                        sibling->colour = 'r';//extra colouring...always try to do so
                        //wherever RED is possible,,it should be added to make tree more balanced
                        return;
                    }
                    else
                    {
                        sibling->colour = 'r';
                        delete_fixup(parent, parent->parent);
                    }


                }
                else//at least one of child sibling is red
                //check this else Logic out one more time during final testing
                {
                    bool left_red = sibling->left->colour=='r' ? true: false;
                    //don't assume that parent is black only
                    if(left_child) //dblack is left child
                    {
                        if(left_red)
                        {
                            rightRotate(sibling);
                            leftRotate(parent);
                            sibling->left->colour = parent->colour;
                        }
                        else
                        {
                                leftRotate(parent);
                                sibling->right->colour = sibling->colour;
                                sibling->colour = parent->colour;
                        }
                        parent->colour = 'b';
                    }
                    else //dblack is right child
                    {
                        if(left_red)
                        {
                            cout<<"yo"<<endl;
                                rightRotate(parent);
                                sibling->left->colour = 'b';
                                sibling->colour = parent->colour;

                                
   
                                
                        }
                        else
                        {
                                leftRotate(sibling);
                                rightRotate(parent);
                                sibling->right->colour = parent->colour;
                        }
                    }
                    //root manipulation
                                 if(parent == root)
                                {
                                    root = parent->parent;
                                    cout<<"so parent was indeed root"<<endl;
                                }
                                         printLinks(root);
                                         Inorder(root);
                }
            }
    }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    public:
    RBNode * LRU_node; //keep updating this node as we go deleting LRU elements
    RBNode * root; //make this private later..this is just for Inorder Traversal testing

    void printLinks(RBNode* node) 
    {
        if (!node) return;
        cout << "Node " << node->key << ": ";
        if (node->left) cout << "Left->" << node->left->key << " ";
        else cout << "Left->NULL ";
        if (node->right) cout << "Right->" << node->right->key << " ";
        else cout << "Right->NULL ";
        if (node->parent) cout << "Parent->" << node->parent->key << " ";
        else cout << "Parent->NULL ";
        cout << "Colour: " << node->colour << endl;
        printLinks(node->left);
        printLinks(node->right);
    }

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
            insert_helper(root,new_node);
            //old root, new_node
        }
        cout<< new_node->key << ":" << new_node->value <<" ("<< new_node->time_stamp <<") colour: "<<new_node->colour <<endl;    
        return new_node;
        //I will thus be returning the new_node's address so that it can be put into the 
        //hashmap also
        
        //hashmap shall have the key followed by node address
    }
    
    void Level_Order()
    {
        queue <RBNode*> q; //lets just store timestamps for now
        //for testing

        q.push(root);

        while(!q.empty())
        {
            cout<<q.front()->key<<" :"<<q.front()->value<<" ("<<q.front()->time_stamp <<")"<<endl;
            if(q.front()->left !=NULL)
            {
                q.push(q.front()->left);
            }
            if(q.front()->right !=NULL)
            {
                q.push(q.front()->right);
            }
            q.pop();
        }
    }

    void Inorder(RBNode * node)
    {
        if(node == NULL) return;

        Inorder(node->left);
        cout<<node->key<<":"<<node->value<<" ("<<node->time_stamp <<") colour: "<<node->colour<<endl;    
        Inorder(node->right);
    }

    RBNode * smallest(RBNode * node)
    {
        if(node->left == NULL) return node;
        else return smallest(node->left);
    }

    RBNode * replacement(RBNode * node)
    {
        //leaf
        if(node->left == NULL && node->right == NULL) return NULL;

        //one child
        if(node->left == NULL) return node->right;
        else if(node->right == NULL) return node->left;

        //else : only option left: both not null
        else return smallest(node->right); //inorder successor
    }

    void swap_data(RBNode * n1, RBNode * n2)
    {
        swap(n1->key, n2->key);
        swap(n1->value, n2->value);
        swap(n1->time_stamp, n2->time_stamp);
    }


    void delete_node(RBNode * v)
    {
        RBNode * rep = replacement(v);
        RBNode * parent = v->parent;
        bool left_child = true;

        if(parent!=NULL)
         left_child = (parent->left == v) ? true: false;

         cout<<"v is "<<v->time_stamp;
         if(left_child) cout<<"  and v is left child"<<endl;
         else cout<<"  and v is right child"<<endl;
         //NEVER DO THIS ON BASIS OF TIMESTAMPS...BECAUSE WE HAVE SWAPPING OCCURING TOO 
        
        bool both_black = (rep == NULL || rep->colour == 'b') && v->colour == 'b' ? true: false;

                // cout<<" v is "<<v->time_stamp<<" and rep is "<<rep->time_stamp<<endl;


        if(both_black) // hence double blacks are going to be created here
        {

            RBNode * d_black;

            if(parent == NULL) //basically this is the root deletion case
            {
                if(rep == NULL)
                {
                    root= NULL;
                    delete(v);
                }
                else if(rep==v->right || rep==v->left)
                {
                        cout<<"okay so parent is NULL for 101"<<endl;
                        swap_data(v,rep);
                        delete_node(rep);
                }
                else
                {
                        swap_data(v,rep);
                        delete_node(rep);
                }

                return;
            }
            else if(rep == NULL) //hence v is leaf
            {
                //enetered here
                if(left_child)
                {
                    parent->left = NULL;
                }
                else
                {
                    parent->right = NULL;
                }
                delete(v);
                d_black = NULL;
                //so HOW will we locate it?-> parent of dblack is still the same as v's parent...
            }
            else if(rep==v->right || rep==v->left) // rep is a child of v..AND a leaf
            {
                
                if(left_child) 
                {
                    parent->left = rep;
                    rep->parent = parent;
                    delete(v);
                }
                else
                {
                    parent->right = rep;
                    rep->parent = parent;
                    delete(v);
                }
                
                d_black = rep;

            }
            else //rep is inorder successor of v
            {
                swap_data(v,rep);
                delete_node(rep); //recur this to the rep node now
                //also, rep is always a leaf node in this case so the value it gets doesn't matter
                //now if rep is red...itll be direct deleted..but this is both black case
                // else it will get a delete_fixup workout 
            }

            //Now time for dblack fixing
            cout<<"okay so far";
            delete_fixup(d_black, parent);
            //parent is just in case dblack is NULL

        }
        else //on of them is red..easier case
        {
            //copy data from rep to v and delete one of them

            if(rep == NULL) //hence v is leaf
            {

                if(left_child)
                {
                    parent->left = NULL;
                }
                else
                {
                    parent->right = NULL;
                }
                delete(v);
            }
            else if(rep==v->right || rep==v->left) // rep is a child of v..AND a leaf
            {
                if(parent == NULL) //v can even be the root..so it Must be black
                {
                    if(rep == v->right)
                    {
                        rep->left = v->left;
                        v->left->parent = rep;
                    }
                    else
                    {
                        rep->right =v->right;
                        v->right->parent = rep;
                        
                    }

                    root = rep;
                    rep->colour = 'b';
                    rep->parent = NULL;
                    delete(v);
                }
                else if(left_child) 
                {
                    parent->left = rep;
                    rep->parent = parent;
                }
                else
                {
                    parent->right = rep;
                    rep->parent = parent;
                }
                rep->colour = 'b';
                delete(v);

            }
            else //rep is inorder successor of v
            {
                swap_data(v,rep);
                v->colour = 'b';
                delete_node(rep); //recur this to rep node now
            }
        }
    }


    RBTree()
    {
        root = NULL;
        LRU_node = NULL;
    }

};


int main()
{
    RBTree T;
    RBNode * n1 = T.insert(100,1,100);
    RBNode * n2 =T.insert(101,2,101);
    RBNode * n4 = T.insert(103,3,103);
    RBNode * n3 = T.insert(99,3,99);
    RBNode * n5 = T.insert(78,3,78);
    // RBNode * n6 = T.insert(32,3,32);
    // RBNode * n7 = T.insert(356,3,356);
    // RBNode * n8 = T.insert(42,3,42);
    // RBNode * n9 = T.insert(322,3,322);
    // RBNode * n10 = T.insert(123,3,123);
    // RBNode * n11 = T.insert(33,3,33);
    // RBNode * n12 = T.insert(5456,3,5456);
    // RBNode * n13 = T.insert(65,3,65);
    // RBNode * n14 = T.insert(221,3,221);
    // RBNode * n15 = T.insert(3452,3,3452);

    cout<<"end of tree creation"<<endl;

    cout<<endl<<endl<<endl;
    T.Inorder(T.root);
    T.printLinks(T.root);

    T.delete_node(T.root);
    cout<<endl<<endl<<endl<<"Deletion complete"<<endl;
    
    cout<<endl<<endl<<endl<<"yo";
    cout<<"root is"<<T.root->time_stamp<<endl;
    T.Inorder(T.root);
}

