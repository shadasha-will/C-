// NPRG041 C++
// Author: Shadasha Williams
// Implementation of Skip Lists

#include <iostream>
#include <dirent.h>
#include <string>
#include <vector>
#include <math.h>
#include <cstdlib>
#include <stdlib.h>

using namespace std;


// if the P value is not defined in compile time then default to P = 1/2
#ifndef P
#define P 0.5
#endif




//MARK: - class with the structure of the nodes for the skip list
class node {
public:
    int key;
    string file_name;
    // a pointer tht points to the level below the current level
    node *lowerLevel;
    // create a pointer for the next node in the current level
    node *next;
    
    node(int key, int level, string file_name) {
        this->key = key;
        this->file_name = file_name;
        this->next = NULL;
        // allocate memory to the forward pointers
        this->lowerLevel = NULL;
        
    }
};

//MARK: - structure that returns search results a boolean for the results of the search and the last accessed nose
struct search_res {
    node *lastNode;
    bool result;
    
    search_res(node *last, bool res) {
        this->lastNode = last;
        this->result = res;
    }
};

//MARK: - function that returns a random float value from 0 to 1 noninclusive
float coin_flip() {
    float result;
    result = ((double) rand() / (RAND_MAX));
    return result;
};

//MARK: - class for the skip list and all of the functions
class skipList {
    // maximum level for the skip list
    int maxlevel;
    // current level of the skip list
    int level;
    float p;
    // pointer to the head node and the tail node
    node *head;
public:
    //MARK: - constructor  for the class
    skipList(int N, float p){
        // intialize the list with the p value, maximum level value, and an initial level of 0
        // set the maximum levels to log base p/2 (N)
        this->maxlevel = log10(N) / log(p/2);
        this->p = p;
        level = 0;
        // set the head node to zero
        head = NULL;
        
    }
    //MARK: - function to traverse through the skip list to find a node in the skip list
    search_res traverse_list(int key) {
        // start at the head node and traverse to the bottom most most level of the skip list
        search_res results;
        node *current;
        current = this->head;
        bool found = false;
        while(current->key != key){
            node *next;
            next = current->next;
            if (next != NULL){
                // check to see if we should move to the next node
                if (next->key < key) {
                    // TODO: find the right order to search the keys
                    
                }
                if (next->key == key){
                    
                }
            }
            
            else {
                
            }
        }
        
        
    }
    
    //MARK: - function to insert a node into a higher level
    void insert_node(int level, node *toInsert) {
        // insert node into the lowest level
        
        // check of the level is  higher than the current level of the tree
        if (level > this->level) {
            // create a new head node
            node *newHead;
            newHead = new node(-1, level, "HEAD");
            newHead->next = toInsert;
            this->head = newHead;
            for(int i = (level - 1); i > this->level; i--) {
                // for every level in between the old maximum level and the new create below nodes
                node *headBelow;
                headBelow = new node(-1, i, "HEAD");
                headBelow->next = toInsert;
                newHead->lowerLevel = headBelow;
                newHead = headBelow;
            }
            // update the new level of the skip list
            int old_level;
            old_level =
            this->level = level;
            
        }
    }
    
    //MARK: - function to push lower nodes being inserted to higher levels
    int promote_node(node *toInsert){
        // start from the lowest level and flip a coin to see if the node should be pushed a level up
        int currLevel;
        currLevel = 1;
        float res = coin_flip();
        if (res > P){
            // flip a coin another coin until the max level until we get the appropriate value
            while((res > P) && (currLevel < maxlevel)) {
                // while the coin is over then keep going up a level
                currLevel++;
                res = coin_flip();
            }
            
        }
        return currLevel;
    }
    
    //MARK: - function for inserting a new node into the skip list
    void insert(const int k, string name) {
        int level_insert;
        node *toInsert;
        toInsert = new node(k, 1, name);
        // check to see if the skip list is empty
        if(head == NULL) {
            // if the list is empty make a new head on the first level and set the new node to the
            // head's next and all other nodes to null
            this->head = new node(-1, 0, "HEAD");
            this->head->lowerLevel = NULL;
            this->head->next = toInsert;
            toInsert->lowerLevel = NULL;
            toInsert->next = NULL;
            this->level = 1;
        }
        
        
        else {
            search_res results = traverse_list(k);
            // TODO: create the search function
            
        }
        
        level_insert = promote_node(toInsert);
        if (level_insert > 1) {
            // check if the node should be inserted into multiple levels
            insert_node(level_insert, toInsert);
            return; }
        
        
    }
    
    
    
};

//MARK: - Main function that reads the files in a folder
int main(int argc, char *argv[]) {
    
    struct dirent *pDirent;
    DIR *dircont;
    
    // open the directory where files are stored
    //dircont = opendir (argv[1]);
    dircont = opendir ("/Users/willshad/skip_list/test_dir");
    if(dircont == NULL) {
        // if the contents of the directory are empty then exit
        cout << "Error! Trying to index and empty directory or a file " << endl;
        return 1;
    }
    // create a vector for reading the file names in a directory
    vector<string> filenames;
    // read the contents of the current directory
    while((pDirent = readdir(dircont)) != NULL) {
        string fname;
        fname = pDirent->d_name;
        // if the file name is a file with valid contents then append to the list of files
        if((fname != ".") || (fname != "..")) {
            filenames.push_back (fname);
        }
    }
    closedir(dircont);
    int dirSize;
    dirSize = (int) filenames.size();
    // create an instance of the skip list for the index
    skipList *ind;
    ind = new skipList(dirSize, P);
    // insert the items in the directory vector to the skiplist index
    for(int i = 0; i < dirSize; i++ ){
        // create a integer for each file that represents a key
        int fileKey = rand() % (dirSize + 100);
        ind->insert(fileKey, filenames[i]);
    }
    return 0;
}
