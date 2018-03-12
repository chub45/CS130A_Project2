//Header file for the AVL Tree
#ifndef AVL_TREE
#define AVL_TREE

#include <fstream>
#include <string>

class AVL{
private:
struct Node{

    int height;
    std::string word;
    int count;
    Node* left;
    Node* right;

};

public:
//default constructor
AVL();
//methods
bool search(std::string value){ return searchHelper(root, value);}
Node* insert(std::string value){ return insertHelper(root, value);}
void remove(std::string value){ removeHelper(root, value);}
void sort();
void rangeSearch(std::string minValue, std::string maxValue){ 
    rangeSearchHelper(root, minValue, maxValue);}
//destructor
~AVL();

private:
Node* root;

//helper methods
bool searchHelper(Node*& root, std::string value);
Node* insertHelper(Node*& root, std::string value);
Node* removeHelper(Node*& root, std::string value);
void removeNode(Node*& root);
void findMinHelper(Node* root, std::string value);
void sortHelper(Node* root, std::ofstream &myfile);
void rangeSearchHelper(Node* root, std::string &minValue, std::string &maxValue);
void Delete(Node*& root);
//rotate methods
Node* rotateRight(Node* root);
Node* rotateLeft(Node* root);

//find higher height method
int max(int left, int right);
int height(Node* root);
};
#endif
