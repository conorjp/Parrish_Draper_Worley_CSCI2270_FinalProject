//
//  FinalProject.cpp
//
//  Final Project
//  CSCI-2270
//  Conor Parrish, James Draper, Luke Worley
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "HashTable.h"

using namespace std;

int main(int argc, char* argv[]){
    HashTable *map = new HashTable();
    string fileName = argv[1];
    ifstream in;
    in.open(fileName);
    string title;
    if(in.is_open()){
        while(!in.eof()){
            getline(in, title);
            map->insertLocation(title, 10);
        }
    }
    in.close();
    
    //GAMEPLAY
    
    return 0;
}