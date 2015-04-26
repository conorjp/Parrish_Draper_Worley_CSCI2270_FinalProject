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
    
    Map->printMap();
    
    //GAMEPLAY
    Location *current = Map->findLocation("inside the pineapple");
    while(current->lives > 0 && Map->allVisited() == false){
        Map->addToOrder(current->title);
        cout << "test" << endl;
        if(current->title == "inside the pineapple"){
            current = Map->pineapple();
        }
        else if(current->title == "under a rock"){
            current = Map->rock();
        }
        else if(current->title == "at the chum bucket"){
            current = Map->chumBucket();
        }
        else if(current->title == "at the krusty krab"){
            current = Map->krustyKrab();
        }
        else if(current->title == "at the salty spitoon"){
            current = Map->saltySpitoon();
        }
        else if(current->title == "at sandy's treedome"){
            current = Map->treedome();
        }
        else{
            cout << "You look lost. Back to the pineapple with you!" << endl;
            current = Map->findLocation("inside the pineapple");
        }
    }
    return 0;
}
