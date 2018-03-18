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
bool searchHelper(Node* node, std::string value);
Node* insertHelper(Node*& node, std::string value);
Node* removeHelper(Node*& node, std::string value);
void removeNode(Node*& node);
void findMinHelper(Node* node, std::string& value);
void sortHelper(Node* rooto, std::ofstream &myfile);
void rangeSearchHelper(Node* node, std::string &minValue, std::string &maxValue);
void Delete(Node*& root);
//rotate methods
Node* rotateRight(Node*& node);
Node* rotateLeft(Node*& node);

//find higher height method
int max(Node*& left, Node*& right);
int height(Node* node);
};
#endif
