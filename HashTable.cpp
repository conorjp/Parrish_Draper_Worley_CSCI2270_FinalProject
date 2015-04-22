//
//  HashTable.cpp
//  
//
//  Created by Conor Parrish on 4/13/15.
//
//

#include <iostream>
#include <vector>
#include "HashTable.h"

using namespace std;

HashTable::HashTable(){
    table = vector<Movie*> (tableSize);
    for(int i=0; i<tableSize; i++){
        table[i] = NULL;
    }
}
HashTable::~HashTable(){
    
}
void HashTable::insertMovie(std::string in_title, int year){
    int index = hashSum(in_title);
    Movie *temp = new Movie(in_title, year);
    if(table[index] != NULL){
        temp->next = table[index];
        if(temp->title < table[index]->title){
            table[index] = temp;
        }
        else{
            Movie *track = NULL;
            Movie *track2 = NULL;
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
Movie* HashTable::findMovie(std::string in_title){
    int index = hashSum(in_title);
    if(table[index] != NULL){
        Movie *temp = table[index];
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
void HashTable::deleteMovie(std::string in_title){
    Movie* mov = findMovie(in_title);
    if(mov == NULL){ //Movie does not exist
        cout << "not found" << endl;
    }
    else{
        int index = hashSum(in_title);
        Movie *temp = table[index];
        if(temp->title == in_title){ //Movie to be deleted is head of list
            //cout << "head of list" << endl;
            if(temp->next == NULL){ //Is only movie in list
                table[index] = NULL;
                delete temp;
            }
            else{ //Is not only movie
                table[index] = temp->next;
                delete temp;
            }
        }
        else{ //Movie to be deleted is not head of list
            //cout << "not head of list" << endl;
            while(temp->next != NULL){
                if(temp->next->title == in_title){ //If next node is Movie to be deleted
                    Movie *temp2 = temp->next;
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
void HashTable::printInventory(){
    bool isEmpty = true;
    for(int i=0; i<table.size(); i++){
        if(table[i] != NULL){
            isEmpty = false;
            Movie *x = table[i];
            while(x != NULL){
                cout << x->title << ":" << x->year << endl;
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