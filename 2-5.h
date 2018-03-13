//Header file for the AVL Tree
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
bool search(std::string value){ return searchHelper(root, value);}
void insert(std::string value){ insertHelper(root, value);}
void remove(std::string value){ removeHelper(root, value);}
void sort();
void rangeSearch(std::string minValue, std::string maxValue){ 
    rangeSearchHelper(root, minValue, maxValue);}
//destructor
~TwoFiveTree();

private:
TwoFiveNode* root;
Node* tracker;

//helper methods
//void makeTwoFive(TwoFiveNode* root, int degree, bool leaf);
void insertVacant(TwoFiveNode* root, std::string value);
void splitChild(TwoFiveNode* newRoot, int index, TwoFiveNode* root);
bool searchHelper(TwoFiveNode* root, std::string value);
void insertHelper(TwoFiveNode* root, std::string value);
Node* removeHelper(TwoFiveNode* root, std::string value);
void sortHelper(TwoFiveNode* root, std::ofstream &myfile);
void rangeSearchHelper(TwoFiveNode* root, std::string value1, std::string value2);
void Delete(TwoFiveNode* root);
//rotate methods
Node* rotateRight(Node* root);
Node* rotateLeft(Node* root);

//find higher height method
int max(Node* left, Node* right);
int height(Node* root);
};
#endif
