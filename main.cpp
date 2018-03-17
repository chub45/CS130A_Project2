//File that reads input and compares the running times of BST and Hash Tables
//Benson Chu
#include "avl.h"
#include "2-5.h"
#include <ctime>
#include <iostream>
#include <cstdlib>
#include <sstream>
#include <fstream>
#include <experimental/filesystem>
using namespace std;
namespace fs = std::experimental::filesystem;
int main(){
    vector <string> store;
    string str;
    int size = 0;
    for(auto& p: fs::recursive_directory_iterator("hotelssmall")){
        if(is_regular_file(status(p))){
            ifstream inFile(p.path());
            if(!inFile){
                cerr << "Unable to open file";
                exit(1);
            }
            while(getline(inFile, str)){
                istringstream stream(str);
                string word;
                while(stream >> word){
                    unsigned int strCount = 0;
                    if(word.length() > 1){
                    for(unsigned int i = 0; i < word.length(); i++){
                        if(isalpha(word.at(i)) || (ispunct(word.at(i)) &&
                            (word.at(i) == '_' ||
                            word.at(i) == ',' ||
                            word.at(i) == '.' ||
                            word.at(i) == '-'))){
                                strCount++;
                        }
                    }
                    }
                    if(strCount == word.length()){
                        size++;
                        store.push_back(word);
                    }
                }
            }
            inFile.close();
        }
    }
    
    //Begin construction of AVL and 2-5
    AVL testAVL;
    TwoFiveTree testTwoFive;
    string input = "";
    cout << size << " words inserted" << endl;
    //Inserting each word into both AVL and TwoFive
    for(unsigned int i = 0; i < store.size(); i++){
        testAVL.insert(store[i]);
        testTwoFive.insert(store[i]);
    }
    do{
        getline(cin, input);
        stringstream storeString(input);
        int command = 0;
        storeString >> command;
        switch(command){
            //perform search function
    case 1: 
    {       string input = "";
            cin >> input;
            int start_b = clock();
            //for(int i = 0; i < 100; i++){
            testAVL.search(input);
            //testAVL.search(store[i]);
            //}
            int stop_b = clock();
            int start_h = clock();
            //for(int i = 0; i < 100; i++){
            testTwoFive.search(input);
            //testTwoFive.search(store[i]);
            //}
            int stop_h = clock();
            if(testAVL.search(input) == testTwoFive.search(input)){
            cout << boolalpha << testTwoFive.search(input) << endl;
            cout << "AVL: " << (stop_b - start_b)/double(CLOCKS_PER_SEC) << "s" << endl;
            cout << "2-5: " << (stop_h - start_h)/double(CLOCKS_PER_SEC) << "s" << endl;
            cout << endl;
            }
    }
            break;
            //perform insert function
    case 2: 
    {      // string input2;
           // cin >> input2;
            int start2_b = clock();
            for(int i = 0; i < 100; i++){
            //testAVL.insert(input2);
            testAVL.insert(store[i]);
            }
            int stop2_b = clock();
            int start2_h = clock();
            for(int i = 0; i < 100; i++){
            //testTwoFive.insert(input2);
            testTwoFive.insert(store[i]);
            }
            int stop2_h = clock();
            cout << "AVL: " << (stop2_b - start2_b)/double(CLOCKS_PER_SEC) << "s" << endl;
            cout << "2-5: " << (stop2_h - start2_h)/double(CLOCKS_PER_SEC) << "s" << endl;
            cout << endl;
            break;
    }
            //perform delete function
    case 3: 
    {       //string input3 = "";
            //cin >> input3;
            int start3_b = clock();
            for(unsigned int i = 0; i < 100; i++){
            //testAVL.remove(input3);
                testAVL.remove(store[i]);
            }
            int stop3_b = clock();
            int start3_h = clock();
            for(unsigned int i = 0; i < 100; i++){
            //testTwoFive.remove(input3);
                testTwoFive.remove(store[i]);
            }
            int stop3_h = clock();
            cout << "AVL: " << (stop3_b - start3_b)/double(CLOCKS_PER_SEC) << "s" << endl;
            cout << "2-5: " << (stop3_h - start3_h)/double(CLOCKS_PER_SEC) << "s" << endl;
            cout << endl;
            break;
    }
            //perform sort function, reads in file to be written to
    case 4: 
    {       int start4_b = clock();
            //testAVL.sort();
            int stop4_b = clock();
            int start4_h = clock();
            testTwoFive.sort();
            int stop4_h = clock();
            cout << "output.txt" << endl;
            cout << "AVL: " << (stop4_b - start4_b)/double(CLOCKS_PER_SEC) << "s" << endl;
            cout << "2-5: " << (stop4_h - start4_h)/double(CLOCKS_PER_SEC) << "s" << endl;
            cout << endl;
            break;
    }
            //perform range search function, requires 2 string inputs
    case 5: 
    {       string rangeMin = "", rangeMax = "";
            cin >> rangeMin >> rangeMax;
            int start5_b = clock();
            testAVL.rangeSearch(rangeMin, rangeMax);
            int stop5_b = clock();
            cout << endl;
            int start5_h = clock();
            testTwoFive.rangeSearch(rangeMin, rangeMax);
            int stop5_h = clock();
            
            cout << "AVL: " << (stop5_b - start5_b)/double(CLOCKS_PER_SEC) << "s" << endl;
            cout << "TwoFive: " << (stop5_h - start5_h)/double(CLOCKS_PER_SEC) << "s" << endl;
            cout << endl;
            break;
    }
        }
    }
    while(true);
    
}
