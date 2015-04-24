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
    
    string playerName, difficulty;
    cout << "Welcome to Bikini Bottom. Please enter your first name" << endl;
    cin >> playerName;
    cout << "Hello " << playerName << ", easy or hard?" << endl;
    cin >> difficulty;
    int diff = 4;
    if(difficulty == easy){
        diff = 4;
        cout << "Starting easy game" << endl;
    }
    else if(difficulty == hard){
        diff = 2;
        cout << "Starting hard game" << endl;
    }
    else{
        cout << "Command not recognized, starting easy game" << endl;
    }
    
    if(in.is_open()){
        while(!in.eof()){
            getline(in, title);
            map->insertLocation(title, diff);
        }
    }
    in.close();
    //GAMEPLAY
    
    return 0;
}