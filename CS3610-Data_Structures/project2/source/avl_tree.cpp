//***************************************************************
//
//  Author: Zach Tumbleson
//  Class : CS3610
//  Date  : 10-10-17
//  Brief : Class implementation of
//          the AVL tree data structure.
//
//  Note  : For sake of transparency, much of this solution is
//          based on the AVL Tree model given in Chapter 11 of
//          Data Structures with C++, 2nd Ed., by D.S. Malik.
//
//***************************************************************





#include <iostream>
#include "avl_tree.h"
#include <algorithm> //for max(a,b) function

void AVLTree::insert(const int key) {
    BinaryNode* newNode = new BinaryNode(key);
    bool isTaller = false;
    
    insert(root, newNode, isTaller);
}

void AVLTree::insert(BinaryNode* &root, BinaryNode* node, bool& isTaller) {
    if (root == NULL) {
        isTaller = true;
        root = node;
    }
    else if(node->key == root->key)
        std::cout << "Duplicate key detected.\n";
    else if(node->key < root->key) {        //insert to the left
            insert(root->left, node, isTaller);
        
            if (isTaller){                  //If the tree is taller, check balance factors for needed
                switch (root->bfactor)      //adjustments.
                {
                case -1:                    //If a tree was left high and an additional node was
                    balanceLeft(root);      //inserted into its left subtree, the current tree is unbalanced.
                    isTaller = false;       //After balancing, the new tree is not taller.
                    break;
                    
                case 0:
                    root->bfactor = -1;     //If a tree was balanced and a node was inserted to the left
                    isTaller = true;        //subtree, the tree is now left high. The left subtree is taller,
                    break;                  //so the tree is also taller
                    
                case 1:
                    root->bfactor = 0;      //If the tree was right high and a new node is inserted
                    isTaller = false;       //into the left subtree, the tree is now balanced. The left
                    break;                  //subtree will be balanced, so the height of the tree will not
                default:                    //increase
                        ;
                }
            }
    }
    else {                                      // node->key > root->key, insert to the right
            insert(root->right, node, isTaller);
        
            if (isTaller){                      //if the tree is taller, tree may need balanced, let's check
                switch (root->bfactor){
                    case -1:
                        root->bfactor = 0;      //If the tree was left high and a node was inserted
                        isTaller = false;       //to the right subtree, then the tree is balanced.
                        break;                  //Since the left subtree was taller, adding to the right
                    case 0:                     //will not increase the height of the tree.
                        root->bfactor = 1;
                        isTaller = true;       //If the tree is balanced, adding a node to the right subtree
                        break;                 //will cause it to become right high. Since tree is right
                                               //high, height of the tree has increased.
                    case 1:
                        balanceRight(root);    //If the tree is right-high, adding a new node to the right
                        isTaller = false;      //will unbalance one of the right subtrees. After balancing,
                        break;                 //the new tree is not taller than the original.
                        
                    default:
                        ;
                }
            }
    }
}

//Rotates the tree to the left
void AVLTree::rotateLeft(BinaryNode* &root)
{
    BinaryNode* node;               // Is eventually a pointer to root->right
    
    if(root == NULL){
        std::cout << "Tree does not exist.\n";
        return;
    }
    else if(root->right == NULL){
        std::cout << "Right subtree is missing.\n";
        return;
    }
    else{
        node = root->right;         // node points to the right subtree of node
        root->right = node->left;   // Root->right points to the left subtree of node
        node->left = root;          // Root is now the left subtree of node
        root = node;                // Make node the new root
    }
}

//Rotates the tree to the right
void AVLTree::rotateRight(BinaryNode* &root)
{
    BinaryNode* node;       //Is eventually a pointer to root->left
    
    if(root == NULL){
        std::cout << "Tree does not exist.\n";
        return;
    }
    else if(root->left == NULL){
        std::cout << "Left subtree is missing.\n";
        return;
    }
    else{
        node = root->left;          // node points to the left subtree of node
        root->left = node->right;   // Root->left points to the right subtree of node
        node->right = root;         // Root is now the right subtree of node
        root = node;                // Make node the new root
    }
}

void AVLTree::balanceLeft(BinaryNode* &root)
{
    BinaryNode* node1;
    BinaryNode* node2;
    
    node1 = root->left;
    
    switch  (node1->bfactor)
    {
        case -1:                                           //Tree is left high
            root->bfactor = 0;                             //After rotation, root subtrees are balanced,
            node1->bfactor = 0;                            //node1 is the root of new balanced AVL tree
            rotateRight(root);
            break;
            
        case 0:                                            //Tree is balanced
            std::cout << "Tree is already balanced.\n";
            break;
        case 1:                                            //Tree is right high
            node2 = node1->right;
            switch (node2->bfactor)
            {
                case -1:
                    root->bfactor = 1;
                    node1->bfactor = 0;
                    break;
                case 0:
                    root->bfactor = 0;
                    node1->bfactor = 0;
                    break;
                case 1:
                    root->bfactor = 0;
                    node1->bfactor = -1;
                    break;
                default:
                    ;
            }
            
            node2->bfactor = 0;
            rotateLeft(node1);
            root->left = node1;
            rotateRight(root);
            break;
        default:
            ;
    }
}

void AVLTree::balanceRight(BinaryNode* &root)
{
    BinaryNode* node1;
    BinaryNode* node2;
    
    node1 = root->right;
    
    switch  (node1->bfactor)
    {
        case -1: //Right subtree is left high
            node2 = node1->left;
            switch (node2->bfactor) //fix balance factors
            {
            case -1:
                root->bfactor = 0;
                node1->bfactor = 1;
                break;
            case 0:
                root->bfactor = 0;
                node1->bfactor = 0;
                break;
            case 1:
                root->bfactor = -1;
                node1->bfactor = 0;
                break;
                default:
                ;
            }
            
            node2->bfactor = 0;
            rotateRight(node1);
            root->right = node1;
            rotateLeft(root);
            break;
            
        case 0: //Tree is balanced
            std::cout << "Tree is already balanced.\n";
            break;
        case 1: // tree is right high
            root->bfactor = 0;  //Root will not be root after rotation
            node1->bfactor = 0; //AVL tree should be balanced after rotation
            rotateLeft(root);
            break;
        default:
            ;
    }
    
}

void AVLTree::remove(const int key)
{
    bool isShorter = false;
    deleteNode(root,key, isShorter);
}

//Returns inorder predecessor of parent of root
BinaryNode *AVLTree::getPred(BinaryNode* root)
{
    if(root->right == NULL) //binary tree must have more than one node.
        return root;
    else{
        getPred(root->right); //rightmost node in the left subtree will contain the inorder predecessor
    }
    return NULL;
}

//Returns inorder successor of parent of root
BinaryNode *AVLTree::getSucc(BinaryNode* root)
{
    static int i = 0;
    if(root->left == NULL){
        //binary tree must have more than one node.
        return root;
    }
    else{
        getPred(root->left); //rightmost node in the left subtree will contain the inorder predecessor
        
    }
    return NULL;
}

//Deletion
void AVLTree::deleteNode(BinaryNode* &root, const int key, bool &isShorter)
{
    if(root == NULL)
        return;
    else if(key < root->key){ //key is less than key of current node, go left
        deleteNode(root->left, key, isShorter);
        //Node has been deleted (or not), check for balancing issues
        if(isShorter){
            switch (root->bfactor){
                    
                case -1:    //Tree was already left high, removing a node from the left balances it
                    root->bfactor = 0;
                    isShorter = true;  //Removing a node from the taller subtree decreases the height
                    break;
                    
                case 0:     //Tree was balanced, removing a node from the left makes it right high
                    root->bfactor = 1;
                    isShorter = false;      //decreasing the height of a balanced tree does not decrease
                    break;                  // the height
                    
                case 1:     //Tree was right high, removing from left creates an imbalance.
                    balanceRight(root);     // Right is now imbalanced, adjust from the right.
                    root->bfactor = 0;
                    isShorter = false;
            }
        }
    }
    else if(key > root->key){ //key is greater than key of current node, go right
        deleteNode(root->right,key, isShorter);
        //deletion is completed (or not), check for imbalances in the tree
        if(isShorter){
            switch (root->bfactor){
                case -1:                //Tree was left high, removing from right causes imbalance
                    balanceLeft(root);
                    root->bfactor = 0;  //After rebalancing, tree is not shorter.
                    isShorter = false;
                    break;
                
                case 0:                 //Tree was balanced, removing from right causes tree to be left high
                    root->bfactor = -1;
                    isShorter = false;  //Tree was balanced, so removing a node does not decrease height
                    break;
                
                case 1:                 //Tree was right-high, removing from the right restores the balance
                    root->bfactor = 0;
                    isShorter = true;   //The tree is shorter since a node was removed from the longer side
                    break;
                default:
                    ;
            }
        }
    }
    else{                    //key is equal to the key of the current node; delete the current node
        
        BinaryNode* tmp = NULL;     //Temporary node used for deletions
        if(root->left == NULL || root->right == NULL){ //Node has one or no children
            
            
            
            if(root->left == NULL && root->right == NULL){ //Case with no child nodes
                tmp = root;
                root = NULL;
                delete tmp;
                isShorter = true;
            }
            else if(root->left == NULL){     //Node has one child at root->right
                tmp = root;
                root = root->right;
                delete tmp;
                isShorter = true;
            }
            else{   //Node has one child at root->left
                tmp = root;
                root = root->left;
                delete tmp;
                isShorter = true;
            }
        }
        else{                                        //Node has two children
                tmp = getPred(root->left);  //Returns the inorder predecessor of the node to be
                                                       //deleted.
                root->key = tmp->key; //Copy predecessor value to root
                deleteNode(root->left, tmp->key, isShorter);
            
                //Node deleted was from the left subtree, check for imbalances
                if(isShorter){
                    switch (root->bfactor){
                        
                        case -1:    //Tree was already left high, removing a node from the left balances it
                            root->bfactor = 0;
                            isShorter = true;  //Removing a node from the taller subtree decreases the height
                            break;
                        
                        case 0:     //Tree was balanced, removing a node from the left makes it right high
                            root->bfactor = 1;
                            isShorter = false;      //decreasing the height of a balanced tree does not
                            break;                  //decrease the height
                    
                        case 1:     //Tree was right high, removing from left creates an imbalance.
                            balanceRight(root);     // Right is now imbalanced, adjust from the right.
                            root->bfactor = 0;
                            isShorter = false;
                            break;
                        default:
                            ;
                    }
                }
        }
    }
}


//Begin Printing functions
void AVLTree::print(const char choice) const
{
    if(choice == 'p'){
        inOrder(root);
        std::cout << std::endl;
    }
    else if(choice == 'h'){
        printHeights(root);
        std::cout << std::endl;
    }
    else
        return;
}

//Prints the result of an inoder tree traversal
void AVLTree::inOrder(const BinaryNode* root) const
{
    if(root == NULL){
        return;
    }
    else if (root->left == NULL && root->right == NULL)
        std::cout << root->key << " ";
    else{
        inOrder(root->left);
        std::cout << root->key << " ";
        inOrder(root->right);
    }
}

//Prints the height of each node in an inorder tree traversal
void AVLTree::printHeights(const BinaryNode* root) const{
    
    if(root == NULL)
        return;
    else{
        printHeights(root->left);
        std::cout << treeHeight(root) << " ";
        printHeights(root->right);
    }
}

//Returns the height of a tree
int AVLTree::treeHeight(const BinaryNode* node) const
{
    if(node == NULL)
        return 0;
    else{
        return std::max(treeHeight(node->left), treeHeight(node->right)) + 1;
    }
}


