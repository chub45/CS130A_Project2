//Implementation for AVL Tree

#include <fstream>
#include <cassert>
#include <iostream>
#include "avl.h"


using namespace std;

//constructor
AVL::AVL(){
    root = NULL;
}

//search
bool AVL::searchHelper(Node* root, string value){
    if(root == NULL){
        return false;
    }
    else if(root->word > value){
        return searchHelper(root->left, value);
    }
    else if(root->word < value){
        return searchHelper(root->right, value);
    }
    else{
        return true;
    }
}

//insert
AVL::Node* AVL::insertHelper(Node* root, string value){
    if(root == NULL){
        root = new Node();
        root->word = value;
        root->count = 1;
    }
    else if(root->word > value){
        insertHelper(root->left, value);
    }
    else if(root->word < value){
        insertHelper(root->right, value);
    }
    else{
        //word is equal to value (already in tree)
        root->count++;
        return root;
    }
    //Checking height and rebalancing now
    int heightCheck = height(root->left) - height(root->right);
    if(heightCheck > 1){
        //left-left case
        if(height(root->left->left) > height(root->left->right)){
            return rotateRight(root);
        }
        //left-right case
        else{
            root->left = rotateLeft(root->left);
            return rotateRight(root);
        }
    }
    else if(heightCheck < -1){
        //right-right case
        if(height(root->right->right) > height(root->right->left)){
            return rotateLeft(root);
        }
        //right-left case
        else{
            root->right = rotateRight(root->right);
            return rotateLeft(root);
        }
    }
    //update height after rebalance
    root->height = 1 + max(root->left, root->right);
    return root;
}

//remove
AVL::Node* AVL::removeHelper(Node* root, string value){
    if(root == NULL){
        return root;
    }
    else if(root->word > value){
        removeHelper(root->left, value);
    }
    else if(root->word < value){
        removeHelper(root->right, value);
    }
    else{
        if(root->count > 1){
            root->count--;
            return root;
        }
        else{
            if(root->left == NULL && root->right == NULL){
                removeNode(root);
                return root;
            }
            else if(root->left == NULL || root->right == NULL){
                removeNode(root);
            }
        }
    }
    //rebalancing tree
    int heightCheck = height(root->left) - height(root->right);
    if(heightCheck > 1){
        //left-left case
        if(height(root->left->left) > height(root->left->right)){
            return rotateRight(root);
        }
        //left-right case
        else{
            root->left = rotateLeft(root->left);
            return rotateRight(root);
        }
    }
    else if(heightCheck < -1){
        //right-right case
        if(height(root->right->right) > height(root->right->left)){
            return rotateLeft(root);
        }
        //right-left case
        else{
            root->right = rotateRight(root->right);
            return rotateLeft(root);
        }
    }
    //update height after rebalance
    root->height = 1 + max(root->left, root->right);
    return root;
}

void AVL::removeNode(Node* root){
    string value;
    Node* temp = root;
    if(root->left == NULL){
        root = root->right;
        delete temp;
    }
    else if(root->right == NULL){
        root = root->left;
        delete temp;
    }
    else{
        findMinHelper(root->right, value);
        root->word = value;
        removeHelper(root->right, value);
    }
}

void AVL::findMinHelper(Node* root, string value){
    while(root->left != NULL){
        root = root->left;
    }
    value = root->word;
}
//sort
void AVL::sort(){
    ofstream myfile;
    myfile.open("output.txt", fstream::app);
    sortHelper(root, myfile);
    myfile << endl;
    myfile.close();
}

void AVL::sortHelper(Node* root, ofstream &myfile){
    if(root != NULL){
        sortHelper(root->left, myfile);
        myfile << root->word << endl;
        sortHelper(root->right, myfile);
    }
}

//range search
void AVL::rangeSearchHelper(Node* root, string minValue, string maxValue){
    if(root == NULL){
        return;
    }
    if(root->word > minValue){
        rangeSearchHelper(root->left, minValue, maxValue);
    }
    if(root->word > minValue && root->word < maxValue){
        cout << root->word << endl;
    }
    if(root->word < maxValue){
        rangeSearchHelper(root->right, minValue, maxValue);
    }
}
//rotate methods, returns new root after rotation
AVL::Node* AVL::rotateRight(Node* root){
    Node* temp = root->left;
    root->left = temp->right;
    temp->right = root;
    root->height = max(root->left, root->right);
    temp->height = max(temp->left, temp->right);
    return temp;
}

AVL::Node* AVL::rotateLeft(Node* root){
    Node* temp = root->right;
    root->right = temp->left;
    temp->left = root;
    root->height = max(root->left, root->right);
    temp->height = max(temp->left, temp->right);
    return temp;
}
//height methods
int AVL::max(Node* left, Node* right){
    if(left != NULL && right != NULL){
        if(left->height > right->height){
            return left->height;
        }
        else if(left->height < right->height){
            return right->height;
        }
        else{
            return left->height;
        }
    }
    else if(left != NULL && right == NULL){
        return left->height;
    }
    else{
        return right->height;
    }
}

int AVL::height(Node* root){
    if(root != NULL){
        return root->height;
    }
    else{
        return -1;
    }
}
