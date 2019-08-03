//***********************************************
//
//  Author: Zach Tumbleson
//  Class : CS3610
//  Date  : 10-10-17
//  Brief : Header file for the AVL Tree data
//          structure.
//
//***********************************************

#ifndef AVL_TREE_H
#define AVL_TREE_H

struct BinaryNode {
    BinaryNode(const int key) : key(key), left(NULL), right(NULL), bfactor(0) {}

    ~BinaryNode() {
        delete left;
        delete right;
        left = right = NULL;
        
    }

    int key, bfactor; // key value and balance factor for a given node
    BinaryNode *left, *right;
};

class AVLTree {

public:
    AVLTree() : root(NULL) {}
    ~AVLTree() {
        delete root;
    }

    void insert(const int key);

//**********************************************************************
//BALANCING FUNCTIONS

private:
    //
    //Precondition: root exists, can be NULL
    //Postcondition: Tree has been rotated left, root->right is the new root
    //
    void rotateLeft(BinaryNode* &root);
    
    //
    //Precondition: root exists, can be NULL
    //Postcondition: Tree has been rotated right, root->left is the new root
    //
    void rotateRight(BinaryNode* &root);
    
    //
    //Precondition: root exists, can be NULL
    //Postcondition: root points to a balanced AVL tree
    //
    void balanceLeft(BinaryNode* &root);
    
    //
    //Precondition: root exists, can be NULL
    //Postcondition: root points to a balanced AVL tree
    //
    void balanceRight(BinaryNode* &root);
    
//***********************************************************************
//DELETION

public:
    //
    //Postcondition: Node with key value equal to key has been deleted
    //
    void remove(const int key);

private:
    //
    //Postcondition: Node matching the value of key has been deleted,
    //               and the tree has been rebalanced.
    //
    void deleteNode(BinaryNode* &root, const int key, bool &isShorter);

//************************************************************************
//PRINTING FUNCTIONS
   
public:
    //
    //Precondition: choice is not NULL, and a valid character
    //Postcondition: If choice was p, node keys have been printed in order.
    //               If choice was h, the heights of the nodes have been printed in order.
    //
    void print(const char choice) const;

private:
    //Precondition: root exists, can be NULL
    //Postcondition: Nodes in the tree have been printed according to an inorder tree traversal.
    //
    void inOrder(const BinaryNode* root) const;
    
    
    
//************************************************************************
//HELPER FUNCTIONS AND MEMBER VARIABLES
    
private:
    
        //
        //Precondition: Node contains a valid key value (integer)
        //Postcondition: Node has been inserted into the appropriate place in the AVL tree.
        //               AVL Tree has been balanced accordingly.
        //
        void insert(BinaryNode* &root, BinaryNode* node, bool& isTaller);
    
        //
        //Precondition: root exists, can be NULL
        //Postcondition: The heights of each node of the binary tree have been printed according to the inorder
        //               traversal.
        void printHeights(const BinaryNode* root) const;
    
        //
        //Precondition: Root exists, can be NULL
        //Postcondition: Returns the longest path from root to leaf, or the height, of the tree
        //
        int treeHeight(const BinaryNode* node) const;
    
        //
        //Precondition: Root points to a non empty tree with at least 2 nodes
        //Postcondition: Returns the node that is the inorder predecessor of the parent of the node that was passed in.
        //
        BinaryNode *getPred(BinaryNode* root);
    
        //
        //Precondition: Tree has a least one node in the right subtree
        //Postcondition: Returns the inorder successor of the parent of the root node passed in
        //
        BinaryNode *getSucc(BinaryNode* root);
    
    
        //************************************
        // MEMBER VARIABLES
    
        BinaryNode* root;
    
        //************************************

};

#endif
