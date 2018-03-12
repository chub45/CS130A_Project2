//Implementation for AVL Tree

#include "avl.h"
#include <fstream>
#include <cassert>
#include <iostream>


using namespace std;

//constructor
AVL::AVL(){
    root = NULL;
}
//search
bool AVL::searchHelper(Node*& root, string value){
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
AVL::Node* AVL::insertHelper(Node*& root, string value){
    if(root == NULL){
        root = new Node();
        root->word = value;
        root->count = 1;
        root->height = 1;
        root->left = NULL;
        root->right = NULL;
        return root;
    }
    if(root->word > value){
        root->left = insertHelper(root->left, value);
    }
    else if(root->word < value){
        root->right = insertHelper(root->right, value);
    }
    else{
        //word is equal to value (already in tree)
        root->count++;
        return root;
    }
    //Checking height and rebalancing now
    root->height = 1 + max(height(root->left), height(root->right));
    int heightCheck;
    if(root->left == NULL && root->right == NULL){
    }
    else if(root->left == NULL){
        heightCheck = 0 - height(root->right);
    }
    else if(root->right == NULL){
        heightCheck = height(root->left) - 0;
    }
    else{
        heightCheck = height(root->left) - height(root->right);
    }
    if(heightCheck > 1){
        //left-left case
        if(value < root->left->word){
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
        if(value > root->right->word){
            return rotateLeft(root);
        }
        //right-left case
        else{
            root->right = rotateRight(root->right);
            return rotateLeft(root);
        }
    }
    //update height after rebalance
    return root;
}

//remove
AVL::Node* AVL::removeHelper(Node*& root, string value){
    if(root == NULL){
        return root;
    }
    else if(root->word > value){
        root->left = removeHelper(root->left, value);
    }
    else if(root->word < value){
        root->right = removeHelper(root->right, value);
    }
    else{
        if(root->count > 1){
            root->count--;
            return root;
        }
        else{
            removeNode(root);
        }
    }
    root->height = 1 + max(height(root->left), height(root->right));

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
    return root;
}

void AVL::removeNode(Node*& root){
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
void AVL::rangeSearchHelper(Node* root, string &minValue, string &maxValue){
    if(root == NULL){
        return;
    }
    if(minValue < root->word){
        rangeSearchHelper(root->left, minValue, maxValue);
    }
    if(minValue < root->word && maxValue > root->word){
        cout << root->word << endl;
    }
    if(maxValue > root->word){
        rangeSearchHelper(root->right, minValue, maxValue);
    }
}
//rotate methods, returns new root after rotation
AVL::Node* AVL::rotateRight(Node* root){
    Node* temp = root->left;
    Node* secondTemp = temp->right;
    temp->right = root;
    root->left = secondTemp;
    root->height = max(height(root->left), height(root->right)) + 1;
    temp->height = max(height(temp->left), height(temp->right)) + 1;
    return temp;
}

AVL::Node* AVL::rotateLeft(Node* root){
    Node* temp = root->right;
    Node* secondTemp = temp->left;
    temp->left = root;
    root->right = secondTemp;
    root->height = max(height(root->left), height(root->right)) + 1;
    temp->height = max(height(temp->left), height(temp->right)) + 1;
    return temp;
}
//height methods
int AVL::max(int left, int right){
    if(left > right){
        return left;
    }
    else{
        return right;
    }
}

int AVL::height(Node* root){
    if(root != NULL){
        return root->height;
    }
    else{
        return 0;
    }
}


//destructor
AVL::~AVL(){
    Delete(root);
}

void AVL::Delete(Node*& root){
    if(root != NULL){
        Delete(root->left);
        Delete(root->right);
        delete root;
    }
}
















