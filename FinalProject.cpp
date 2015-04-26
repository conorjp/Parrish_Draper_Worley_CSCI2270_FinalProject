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
    string location = "pineapple";
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
    Location *current = Map->findLocation("pineapple");
    ifstream in;
    in.open(fileName);
    string title;
    if(in.is_open())
        {
        while(!in.eof()){
            getline(in, title);
            cout<<title<<endl;
            Map->insertLocation(title, diff);
        }
    }
    in.close();
    
    //GAMEPLAY
    while(current->lives > 0 && Map->allVisited() == false){

        Map->printMap();
        cout<<"You are in a pineapple under the sea. Who are you (all lower case one word without pants)."<<endl;
        string name;
        cin >> name;

        if (name == "spongebob")
        {
             cin.ignore(1,'\n');
            cout<<"congratulations you now have the option to visit your friend patrick by typing 'under a rock' or sandy in a tree bubble by typing 'at sandy’s treedome'. Which would you like to do?"<<endl;
            getline(cin,location);
            cout<<location<<endl;
            Map->addToOrder(location);
        }
        else
        {
            Map->setHealth(location);
        }
    }


    return 0;
}
