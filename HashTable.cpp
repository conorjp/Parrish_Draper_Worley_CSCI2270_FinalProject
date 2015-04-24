//
//  HashTable.cpp
//
//  Final Project
//  CSCI-2270
//  Conor Parrish, James Draper, Luke Worley
//

#include <iostream>
#include <vector>
#include "HashTable.h"

using namespace std;

HashTable::HashTable(){
    table = vector<Location*> (tableSize);
    for(int i=0; i<tableSize; i++){
        table[i] = NULL;
    }
}
HashTable::~HashTable(){

}
void HashTable::insertLocation(std::string in_title, int lives){
    int index = hashSum(in_title);
    Location *temp = new Location(in_title, lives);
    if(table[index] != NULL){
        temp->next = table[index];
        if(temp->title < table[index]->title){
            table[index] = temp;
        }
        else{
            Location *track = NULL;
            Location *track2 = NULL;
            while(temp->next != NULL && temp->next->title < temp->title){
                track2 = temp->next;
                temp->next = temp->next->next;
                track2->next = temp;
                if(track == NULL){
                    track = table[index];
                }
                else{
                    track->next = track2;
                    track = track->next;
                }
            }
        }
    }
    else{
        table[index] = temp;
    }
}
Location* HashTable::findLocation(std::string in_title){
    int index = hashSum(in_title);
    if(table[index] != NULL){
        Location *temp = table[index];
        while(temp != NULL){
            if(temp->title == in_title){
                return temp;
            }
            else{
                temp = temp->next;
            }
        }
        return NULL;
    }
    else{
        return NULL;
    }
}
void HashTable::deleteLocation(std::string in_title){
    Location* loc = findLocation(in_title);
    if(loc == NULL){ //Location does not exist
        cout << "not found" << endl;
    }
    else{
        int index = hashSum(in_title);
        Location *temp = table[index];
        if(temp->title == in_title){ //Location to be deleted is head of list
            //cout << "head of list" << endl;
            if(temp->next == NULL){ //Is only location in list
                table[index] = NULL;
                delete temp;
            }
            else{ //Is not only location
                table[index] = temp->next;
                delete temp;
            }
        }
        else{ //Location to be deleted is not head of list
            //cout << "not head of list" << endl;
            while(temp->next != NULL){
                if(temp->next->title == in_title){ //If next node is location to be deleted
                    Location *temp2 = temp->next;
                    temp->next = temp->next->next;
                    delete temp2;
                }
                else{
                    temp = temp->next;
                }
            }
        }
    }
}
void HashTable::printMap(){
    bool isEmpty = true;
    for(int i=0; i<table.size(); i++){
        if(table[i] != NULL){
            isEmpty = false;
            Location *x = table[i];
            while(x != NULL){
                cout << x->title << ":" << x->lives << endl;
                x = x->next;
            }
        }
    }
    if(isEmpty == true){
        cout << "empty" << endl;
    }
}
int HashTable::hashSum(string x){ //x is the string to hash, s is the array size
    int sum = 0;
    for(int i=0; i<x.length(); i++){
        sum =sum + x[i];
    }
    sum = sum % tableSize;
    return sum;
}
void HashTable::setHealth(std::string name, int in_lives){
    Location *toSet = findLocation(name);
    toSet->lives = in_lives;
}
void tryingrepository(string rep)
{
    cout<<rep<<endl;

}


