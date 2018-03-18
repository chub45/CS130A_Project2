//Header file for the 2-5 Tree
#ifndef TWO_FIVE_TREE
#define TWO_FIVE_TREE

#include <fstream>
#include <string>

class TwoFiveTree{
private:

struct Node{
    //array of strings
    std::string word;
    //stores array of count corresponding to values[]
    int count;
};

struct TwoFiveNode{
    //an array of Nodes for 2-5
    Node** keys;
    //lowest number of keys available (t)
    int degree; 
    //array of pointers for children of this node
    TwoFiveNode** children;
    //current size of array (n)
    int keySize;
    //Determine if leaf or not
    bool isLeaf;
};
public:
//default constructor
TwoFiveTree();

//methods
bool search(std::string value){ return searchHelper(node, value);}
void insert(std::string value){ insertHelper(node, value);}
void remove(std::string value){ removeHelper(node, value);}
void sort();
void rangeSearch(std::string minValue, std::string maxValue){ 
    rangeSearchHelper(node, minValue, maxValue);}
//destructor
~TwoFiveTree();

private:
TwoFiveNode* node;
//helper methods
void insertVacant(TwoFiveNode*& root, std::string value);
void splitChild(TwoFiveNode*& newRoot, int index, TwoFiveNode*& root);
bool searchHelper(TwoFiveNode*& root, std::string value);
void insertHelper(TwoFiveNode*& root, std::string value);
void removeHelper(TwoFiveNode*& root, std::string value);
void removeNonLeaf(TwoFiveNode* root, int index);
Node* findMinHelper(TwoFiveNode* root, int index);
Node* findMaxHelper(TwoFiveNode* root, int index);
void swap(TwoFiveNode* root, int index);
void mergeChild(TwoFiveNode* root, int index);
void sortHelper(TwoFiveNode* root, std::ofstream &myfile);
void rangeSearchHelper(TwoFiveNode*& root, std::string value1, std::string value2);
void Delete(TwoFiveNode*& root);

};
#endif
