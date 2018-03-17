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
            //traverse tree to lowest level, then delete children
            Delete(root->children[i]);
            delete root->children[i];
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

bool TwoFiveTree::searchHelper(TwoFiveNode*& root, string value){
    int store = 0;
    if(root == NULL){
        return false;
    }
    else{
        while(store < root->keySize && root->keys[store]->word < value){
            store++;
        }
        if(root->keySize == 1){
            if(root->keys[0]->word == value && !root->isLeaf){
                return true;
            }
            else{
                return searchHelper(root->children[0], value);
            }
        }
        else if(root->keys[store]->word == value){
            return true;
        }
        if(root->isLeaf == true){
            return false;
        }
   }
       if(store < root->keySize + 1)
       return searchHelper(root->children[store], value);
}
//insert method
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
            if(newRoot->keys[0]->word < value){
                insertVacant(newRoot->children[1], value);
            }
            else{
                insertVacant(newRoot->children[0], value);
            }
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
            splitChild(root, i + 1 , root->children[i + 1]);
            if(root->keys[i + 1]->word < value){
                i++;
            }
        }
        insertVacant(root->children[i + 1], value);
    }
}

//method that performs splitting (left has 2 values, right has 1)
void TwoFiveTree::splitChild(TwoFiveNode*& newRoot, int index, TwoFiveNode*& root){
    TwoFiveNode* store = new TwoFiveNode();
    store->degree = root->degree;
    store->isLeaf = root->isLeaf;
    store->keys = new Node*[2 * store->degree];
    if(!store->isLeaf){
        store->children = new TwoFiveNode*[2 * store->degree + 1];
    }
    else{
        store->children = NULL;
    }
    store->keySize = newRoot->degree - 1;
    //copy last key of full node to new node
    store->keys[0] = root->keys[newRoot->degree + 1];

    //copy children of last element
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

    for(int i = newRoot->keySize; i >= index; i--){
        newRoot->keys[i + 1] = newRoot->keys[i];
    }

    newRoot->keys[index] = root->keys[newRoot->degree];
    newRoot->keySize++;
}

//delete/remove method
void TwoFiveTree::removeHelper(TwoFiveNode*& root, string value){
    int i = 0;
    //cases for each delete scenario
    if(root == NULL){
        return;
    }
    else if(node == NULL){
        return;
    }
    else if(node->isLeaf == true){
        if(node->keySize == 1){
            delete node->keys[0];
            return;
        }
    }
    //check to see if value is in current node
    while(i < root->keySize && root->keys[i]->word < value){
     i++;
    }
    if(root->keySize == 1){
        if(root->keys[0]->word != value && !root->isLeaf){
            removeHelper(root->children[i], value);
        }
        else if(root->keys[0]->word == value && !root->isLeaf){
            removeNonLeaf(root, 0);
        }
        else if(root->isLeaf == true){
            delete root->keys[0];
        }
    }
    else if(root->keys[i]->word == value){
        if(root->isLeaf == true){
            //word exists with count > 1
            if(root->keys[i]->count > 1){
                root->keys[i]->count--;
                return;
            }
            else{
                //deallocate memory for current Node with value
                delete root->keys[i];
                //shift values over as necessary
                for(int j = i; j < root->keySize - 1; j++){
                    root->keys[j] = root->keys[j + 1];
                }
                root->keySize--;
           }
        }
        else{//value found not in non-leaf node, complex
            if(root->keys[i]->count > 1){
                root->keys[i]->count--;
            }
            else{
                removeNonLeaf(root, i);
            }
        }
    }
    else{ 
        if(root->isLeaf == true){
        //value not found at leaf level, so not found
            return;
        }
        bool checkMerge = false;
        //child has value that we want to delete
        if(i == root->keySize){
            checkMerge = true;
        }
        //perform a swap with siblings if only has one element
        if(root->children[i]->keySize < root->degree){
            swap(root, i);        
        }

        //check to see if merge was resulted from above if statement
        if(checkMerge){
            removeHelper(root->children[0], value);
        }
        else{
            removeHelper(root->children[i + 1], value);
        }
    }
    return;
}

void TwoFiveTree::removeNonLeaf(TwoFiveNode* root, int index){
    //stored for merging
    string store = root->keys[index]->word;
    //Check if predecessor has more than one value
    if(root->keys[index]->count > 1){
        root->keys[index]->count--;
        return;
    }
    if(root->children[index]->keySize >= root->degree){
       Node* store = findMaxHelper(root, index);
       root->keys[index]->word = store->word;
       root->keys[index]->count = store->count;
       store->count = 1;
       removeHelper(root->children[index], root->keys[index]->word);
    }//child has less than a value, so check successor
    else if(root->children[index + 1]->keySize >= root->degree){
        Node* store = findMinHelper(root, index);
        root->keys[index]->word = store->word;
        root->keys[index]->count = store->count;
        store->count = 1;
        removeHelper(root->children[index + 1], root->keys[index]->word);
    }//Both have less than a value, so merge must occur
    else{
        //moves all values in children[index + 1] and root->keys[index] into children[index]
        mergeChild(root, index);
        //remove value after merge
        removeHelper(root->children[index], store);
    }
    return;
}

//find smallest value in right sibling
TwoFiveTree::Node* TwoFiveTree::findMaxHelper(TwoFiveNode* root, int index){
    TwoFiveNode* temp = root->children[index];
    //traverse to lowest level
    while(temp->isLeaf == false){
        temp = temp->children[temp->keySize];
    }
    
    //leaf level, returns largest value
    return temp->keys[temp->keySize - 1];
}

//find largest value in left sibling
TwoFiveTree::Node* TwoFiveTree::findMinHelper(TwoFiveNode* root, int index){
    TwoFiveNode* temp = root->children[index + 1];
    //traverse to lowest level
    while(temp->isLeaf == false){
        temp = temp->children[0];
    }
    //leaf level, returns smallest value
    return temp->keys[0];
}

//method that takes key from siblings
void TwoFiveTree::swap(TwoFiveNode* root, int index){
    //Check left child for a key
    if(index > 0 && root->children[index - 1]->keySize >= root->degree){
        //take key from left child
        TwoFiveNode* left = root->children[index - 1];
        TwoFiveNode* current = root->children[index];

        //Shift keys of current to the right
        for(int i = current->keySize - 1; i >= 0; i--){
            current->keys[i + 1] = current->keys[i];
        }  

        //Shift children of current to the right
        if(current->isLeaf == false){
            for(int i = current->keySize; i >= 0; i--){
               current->children[i + 1] = current->children[i];
            }
        }

        //Take key from parent
        current->keys[0] = root->keys[index - 1];
            
        //take siblings child and move to 
        if(current->isLeaf == false){
            current->children[0] = left->children[left->keySize];    
        }
        
        root->keys[index - 1] = left->keys[left->keySize - 1];

        current->keySize++;
        left->keySize--;
    }
    else if(index != root->keySize && root->children[index + 1]->keySize >= root->degree){
        //take key from right child
        TwoFiveNode* current = root->children[index];
        TwoFiveNode* right = root->children[index + 1];
        
        current->keys[current->keySize] = root->keys[index];
        
        if(current->isLeaf == false){
            current->children[current->keySize + 1] = right->children[0];
        }       

        root->keys[index] = right->keys[0];
        
        for(int i = 0; i < right->keySize - 1; i++){
            right->keys[i] = right->keys[i + 1];
        }

        if(right->isLeaf == false){
            for(int i = 0; i < right->keySize; i++){
                right->children[i] = right->children[i + 1];
            }
        }

        current->keySize++;
        right->keySize--;
    }
    else{
        //merge last child with left child
        if(index == root->keySize){
            mergeChild(root, index);
        }
        else{//merge child with right child
            mergeChild(root, index + 1);
        }
    }
    
}

//methods that merges children[index + 1] and value at keys[index] into children[index]
void TwoFiveTree::mergeChild(TwoFiveNode* root, int index){
    TwoFiveNode* left = root->children[index];
    TwoFiveNode* right = root->children[index + 1];

    //store keys[index] into left
    left->keys[1] = root->keys[index];
    //store children[index + 1]->keys[0] into children[index]
    left->keys[2] = right->keys[0];
    //copy over children of right to left
    if(left->isLeaf == false){
        left->children[2] = right->children[0];
        left->children[3] = right->children[1];
    }

    //shift current node's keys to compensate for moving keys[index] down
    for(int i = index; i + 1 < root->keySize; i++){
        root->keys[i] = root->keys[i + 1];
    }

    //shift current node's children to compensate for shifting keys
    for(int i = index + 1; i < root->keySize; i++){
        root->children[i] = root->children[i + 1];
    }

    //update keySize for both child (left) and root
    //+ 1 from current node's key
    left->keySize += right->keySize + 1;
    root->keySize--;

    //deallocate memory for right
    delete right;
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

void TwoFiveTree::rangeSearchHelper(TwoFiveNode*& root, string value1, string value2){
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
