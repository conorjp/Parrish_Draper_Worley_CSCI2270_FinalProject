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

int main(){

    //Initial menu
    string playerName, difficulty, nextlocation;
    cout << "Welcome to Bikini Bottom. Please enter your first name" << endl;
    cin >> playerName;
    cout << "Hello " << playerName << ", easy or hard?" << endl;
    cin >> difficulty;
    int diff = 4;
    if(difficulty == "easy"){
        cout << "Starting easy game" << endl;
    }
    else if(difficulty == "hard"){
        diff = 2;
        cout << "Starting hard game" << endl;
    }
    else{
        cout << "Command not recognized, starting easy game" << endl;
    }

    //Read in locations file and build hash table
    HashTable *Map = new HashTable();
    string fileName = "locations.txt";
    ifstream in;
    in.open(fileName);
    string title;
    if(in.is_open())
        {
        while(!in.eof()){
            getline(in, title);
            Map->insertLocation(title, diff);
        }
    }
    in.close();
    
    //GAMEPLAY
    Location *current = Map->findLocation("pineapple");
    while(current->lives > 0 && Map->allVisited() == false){
        Map->addToOrder(current->title);
        if(current->title == "inside the pineapple"){
            current = Map->pineapple();
        }
        else if(current->title == "under a rock"){
            
        }
    }
    return 0;
}
