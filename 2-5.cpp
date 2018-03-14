//Implementation for 2-4 Tree

#include "2-5.h"
#include <fstream>
#include <iostream>
#include <cassert>

using namespace std;

//default constructor
TwoFiveTree::TwoFiveTree(){
    node = NULL;
}

//destructor
TwoFiveTree::~TwoFiveTree(){
   Delete(node); 
}

void TwoFiveTree::Delete(TwoFiveNode*& root){
    if(root->isLeaf == false){
        for(int i = 0; i < root->keySize + 1; i++){
            Delete(root->children[i]);
        }
        for(int i = 0; i < root->keySize; i++){
            delete root->keys[i];
        }
    }
    else{
        for(int i = 0; i < root->keySize; i++){
            delete root->keys[i];
        }
    }
    delete root;
}

bool TwoFiveTree::searchHelper(TwoFiveNode* root, string value){
    int store = 0;
    if(root == NULL){
        return false;
    }
    else{
        while(store < root->keySize && root->keys[store]->word < value){
            store++;
        }
        if(root->keys[store]->word == value){
            return true;
        }
        else if(root->isLeaf == true){
            return false;
        }
    }
    return searchHelper(root->children[store], value);
}
void TwoFiveTree::insertHelper(TwoFiveNode*& root, string value){
    //tree is empty
    if(root == NULL){
        root = new TwoFiveNode();
        root->isLeaf = true;
        root->degree = 2;
        root->keys = new Node*[2 * root->degree];
        root->children = NULL;
        root->keySize = 1;
        root->keys[0] = new Node();
        root->keys[0]->word = value;
        root->keys[0]->count = 1;
    }
    else{
        //if current node is full
         if(root->keySize == (2 * root->degree)){
            //create new root
            TwoFiveNode* newRoot;
            newRoot = new TwoFiveNode();
            newRoot->isLeaf = false;
            newRoot->degree = 2;
            newRoot->keys = new Node*[2 * newRoot->degree];
            newRoot->children = new TwoFiveNode*[2 * root->degree + 1];
            newRoot->keySize = 0;
            newRoot->children[0] = root;
            //split full node
            splitChild(newRoot, 0, root);
            //find correct index to add new value
            int i = 0;
            if(newRoot->keys[0]->word < value){
                i++;
            }
            insertVacant(newRoot->children[i], value);
            root = newRoot;
        }
        else{
            insertVacant(root, value);
        }
    }
}

//method to insert into a TwoFiveNode with space
void TwoFiveTree::insertVacant(TwoFiveNode*& root, string value){
    int i = root->keySize - 1;
    //shift values as necessary
    if(root->isLeaf == true){
        for(int j = 0; j < root->keySize; j++){
            if(root->keys[j]->word == value){
                root->keys[j]->count++;
                return;
            }
        }
        while(i >= 0 && root->keys[i]->word > value){
            root->keys[i + 1] = root->keys[i];
            i--;
        }
        //create new Node
        root->keys[i + 1] = new Node();
        root->keys[i + 1]->count = 1;
        root->keys[i + 1]->word = value;
        root->keySize++;
    }
    else{ //not leaf
        for(int j = 0; j < root->keySize; j++){
            if(root->keys[j]->word == value){
                root->keys[j]->count++;
                return;
            }
        }
        while( i >= 0 && root->keys[i]->word > value){
            i--;
        } //check if child is full
        if(root->children[i + 1]->keySize == 4){
            cout << "child of parent is full, split " << endl;
            splitChild(root, i + 1, root->children[i + 1]);
            if(root->keys[i + 1]->word < value){
                i++;
            }
        }
        insertVacant(root->children[i+1], value);
    }
}

//method that performs splitting (left has 2 values, right has 1)
void TwoFiveTree::splitChild(TwoFiveNode*& newRoot, int index, TwoFiveNode*& root){
    TwoFiveNode* store = new TwoFiveNode();
    store->degree = root->degree;
    store->isLeaf = root->isLeaf;
    store->keys = new Node*[2 * store->degree];
    store->children = new TwoFiveNode*[2 * store->degree + 1];
    store->keySize = newRoot->degree - 1;
    //copy last key of full node to new node
    store->keys[0] = root->keys[newRoot->degree + 1];

    //copy children
    if(root->isLeaf == false){
        for(int i = 0; i < newRoot->degree; i++){
            store->children[i] = root->children[i + newRoot->degree + 1];
        }
    }
    //shift children of root
    root->keySize = newRoot->degree;
    for(int i = newRoot->keySize; i >= index + 1; i--){
        newRoot->children[i + 1] = newRoot->children[i];
    }
    newRoot->children[index + 1] = store;

    for(int i = newRoot->keySize - 1; i >= index; i--){
        newRoot->keys[i + 1] = newRoot->keys[i];
    }

    newRoot->keys[index] = root->keys[newRoot->degree];
    newRoot->keySize++;
}

void TwoFiveTree::sort(){
    ofstream myfile;
    myfile.open("output.txt", fstream::app);
    sortHelper(node, myfile);
    myfile << endl;
    myfile.close();
}

void TwoFiveTree::sortHelper(TwoFiveNode* root, ofstream &myfile){
    if(root != NULL){
        int i;
        for(i = 0; i < root->keySize; i++){
            if(root->isLeaf == false){
                sortHelper(root->children[i], myfile);
            }
            myfile << root->keys[i]->word << endl;
        }
        if(root->isLeaf == false){
            sortHelper(root->children[i], myfile);
        }
    }
}

void TwoFiveTree::rangeSearchHelper(TwoFiveNode* root, string value1, string value2){
    int i;
    if(root == NULL){
        return;
    }
    for(i = 0; i < root->keySize; i++){
        if(root->isLeaf == false){
            rangeSearchHelper(root->children[i], value1, value2);
        }
        if(root->keys[i]->word > value1 && root->keys[i]->word < value2){
            cout << root->keys[i]->word << endl;    
        }
    }
    //last child
    if(root->isLeaf == false){
        rangeSearchHelper(root->children[i], value1, value2);
    }   

}
