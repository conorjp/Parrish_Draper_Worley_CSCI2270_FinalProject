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
    string playerName, difficulty, nextlocation,location;
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
    cout<<"You are in a pineapple under the sea. Who are you (all lower case one word without pants)."<<endl;
    string name;
    cin >> name;

    if (name == "spongebob")
    {
         cin.ignore(1,'\n');
        cout<<"congratulations you now have the option to visit your friend patrick by typing 'under a rock' or sandy in a tree bubble by typing 'at sandy’s treedome'. Which would you like to do?"<<endl;





        cout<<"Enter  title:"<<endl;
        getline(cin,location);
       Map->findLocation(location)->orderVisited ;
        cout<<nextlocation<<endl;
    }
    else
    {
        Map->setHealth(location);
    }


    return 0;
}
