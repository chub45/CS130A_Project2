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
bool AVL::searchHelper(Node* node, string value){
    if(node == NULL){
        return false;
    }
    else if(node->word > value){
        return searchHelper(node->left, value);
    }
    else if(node->word < value){
        return searchHelper(node->right, value);
    }
    else{
        return true;
    }
}

//insert
AVL::Node* AVL::insertHelper(Node*& node, string value){
    if(node == NULL){
        node = new Node();
        node->word = value;
        node->count = 1;
        node->left = NULL;
        node->right = NULL;
        node->height = 1;
        return node;
    }
    else if(node->word == value){
        node->count++;
        return node;
    }
    else if(node->word > value){
        node->left = insertHelper(node->left, value);
    }
    else{
        node->right = insertHelper(node->right, value);
    }
    //Checking height and rebalancing now
    int heightCheck = height(node->left) - height(node->right);
    if(heightCheck > 1){
        //left-left case
        if(height(node->left->left) >= height(node->left->right)){
            return rotateRight(node);
        }
        //left-right case
        else{
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
    }
    else if(heightCheck < -1){
        //right-right case
        if(height(node->right->right) >= height(node->right->left)){
            return rotateLeft(node);
        }
        //right-left case
        else{
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }
    }
    //update height after rebalance
    node->height = 1 + max(node->left, node->right);
    return node;
}

//remove
AVL::Node* AVL::removeHelper(Node*& node, string value){
    if(node == NULL){
        return node;
    }
    else if(node->word > value){
        node->left = removeHelper(node->left, value);
    }
    else if(node->word < value){
        node->right = removeHelper(node->right, value);
    }
    else{
        if(node->count > 1){
            node->count--;
            return node;
        }
        //must delete entire node
        else{
            removeNode(node);
        }
    }
    if(node == NULL){
        return node;
    }
    //rebalancing tree
    int heightCheck = (height(node->left) - height(node->right));
    if(heightCheck > 1){
        //left-left case
        if(height(node->left->left) > height(node->left->right)){
            return rotateRight(node);
        }
        //left-right case`
        else{
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
    }
    else if(heightCheck < -1){
        //right-right case
        if(height(node->right->right) > height(node->right->left)){
            return rotateLeft(node);
        }
        //right-left case
        else{
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }
    }
    //update height after rebalance
    node->height = 1 +  max(node->left, node->right);
    return node;
}

void AVL::removeNode(Node*& node){
    string value;
    Node* temp = node;
    //leaf
    if(node->left == NULL && node->right == NULL){
        delete temp;
        node = NULL;
    }
    else if(node->left == NULL){
        node = node->right;
        delete temp;
    }
    else if(node->right == NULL){
        node = node->left;
        delete temp;
    }
    //has two children
    else{
        findMinHelper(node->right, value);
        node->word = value;
        node->right = removeHelper(node->right, value);
    }
}

void AVL::findMinHelper(Node* node, string& value){
    while(node->left != NULL){
        node = node->left;
    }
    value = node->word;
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
void AVL::rangeSearchHelper(Node* node, string& minValue, string& maxValue){
    if(node == NULL){
        return;
    }
    if(node->word > minValue){
        rangeSearchHelper(node->left, minValue, maxValue);
    }
    if(node->word > minValue && node->word < maxValue){
        cout << node->word << endl;
    }
    if(node->word < maxValue){
        rangeSearchHelper(node->right, minValue, maxValue);
    }
}
//rotate methods, returns new root after rotation
AVL::Node* AVL::rotateRight(Node*& node){
    Node* temp = node->left;
    node->left = temp->right;
    temp->right = node;
    node->height = 1 + max(node->left, node->right);
    temp->height = 1 + max(temp->left, temp->right);
    if(node == root){
        root = temp;
    }
    return temp;
}

AVL::Node* AVL::rotateLeft(Node*& node){
    Node* temp = node->right;
    node->right = temp->left;
    temp->left = node;
    node->height = 1 + max(node->left, node->right);
    temp->height = 1 + max(temp->left, temp->right);
    if(node == root){
        root = temp;
    }
    return temp;
}
//height methods
int AVL::max(Node*& left, Node*& right){
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
    else if(left == NULL && right == NULL){
        return 0;
    }
    else if(left != NULL && right == NULL){
        return left->height;
    }
    else{
        return right->height;
    }
}

int AVL::height(Node* node){
    if(node != NULL){
        return node->height;
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
















