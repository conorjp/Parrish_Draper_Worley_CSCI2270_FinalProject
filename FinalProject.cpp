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

    //Initial menu
    string playerName, difficulty;
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
    cout<<"here"<<endl;
    HashTable *Map = new HashTable();
    cout<<"here"<<endl;
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
    cout<<"You are in a pineapple under the sea. Who are you."<<endl;


    return 0;
}
