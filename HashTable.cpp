//
//  HashTable.cpp
//
//  Final Project
//  CSCI-2270
//  Conor Parrish, James Draper, Luke Worley
//

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include "HashTable.h"

using namespace std;

int livesT;

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
    livesT = lives;
    Location *newLocation = new Location(in_title, lives);
    newLocation->visited = false;
    Location *possible = table[index];

    if (possible == NULL)
    {
        //cout<< index << " "<< in_title<<" no collision"<<endl;
        table[index] = newLocation;
        newLocation->next = NULL;
    }
    else
    {
        //cout<<" collision";
        if (in_title.compare(possible->title)>0) // if in title is after possible  alphabetically
        {

        //cout<<index<<" "<<in_title<<" collision"<<endl;
            while(possible->next!=NULL)
            {
                if(in_title.compare(possible->next->title)<0) // if its supposed to go in the middle
                {
                    break;
                }
                possible = possible -> next;
            }
            //cout<< newLocation -> title <<endl;
            newLocation->next = possible->next;
            possible->next = newLocation;
        }
        else
        {
            //cout<<"head collision"<<endl;
            newLocation->next = possible;
            table[index] = newLocation;
        }
    }
}
//prototype:
//  table.findLocation("location")
//Description:
//  This function takes in the location at which the player would like to be. It goes through our
//  hashtable to find the location and give the player the options associated with that location.
//Pre-Conditions:
//  requires a string as an input
//  you must have built an instance of our hash table and filled it with locations before deleting a location

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
//prototype:
//  map.deleteLocation("string")
// Description:
//  This function deletes a "location" from our hash table. Each of our locations are
//  to determine at what point in our rpg game the player is in.
//Pre-Conditions
//  requires a string as an input
//  you must have built an instance of our hash table and filled it with locations before deleting a location
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
void HashTable::printMap()
{
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
// always decrements lives so that the players current life doesnt need to be known (makes it a little easier) if we want to be able to
// give the player health back we can pass an integer when that integer is greater than zero you add to health and if its less than zero you
// decrement the health
void HashTable::setHealth(std::string name)
{
    Location *toSet = findLocation(name);
    toSet->lives--;
}
//The player must have left the first level for there to be anything to print.
//Everytime the player visits a new location we must assign that new location to the end of our visited linked list.
void HashTable::printPreviousLocations(Location *head)
{
    Location *start = head;
    while (start->orderVisited!=NULL)
    {
        cout<<start->title<< "->"<<endl;
    }

}

//adds the current location to the end of the linked list
void HashTable::addToOrder (string location)
{
    Location* start = head;
    Location* tail = findLocation(location);
    while (start -> orderVisited != NULL) //head is a public member of our  class
    {
        start=start->orderVisited; //(iterate through the order we've visited)

    }
    start->orderVisited = tail;
    tail->orderVisited = NULL;
}
void HashTable::printNotVisitedLocations(Location *head)
{
    bool isEmpty = true;
    for(int i=0; i<table.size(); i++){
        if(table[i] != NULL){
            isEmpty = false;
            Location *x = table[i];
            while(x != NULL){
                if(x->visited==false)
                {
                    cout << x->title << "->";
                }

                x = x->next;
            }
        }
        cout<<endl;
    }
}

//Checks if every location has been visited. If all have been visited and lives != 0, player wins
bool HashTable::allVisited(){
    bool visited = true;
    for(int i=0; i<table.size(); i++){
        if(table[i] != NULL){
            Location *x = table[i];
            while(x != NULL){
                if(x->visited == false){
                    visited = false;
                }
                x = x->next;
            }
        }
    }
    return visited;
}

//LOCATION FUNCTIONS
Location* HashTable::pineapple(){
    Location *currentLoc = findLocation("inside the pineapple");
    currentLoc->visited = true;
    string name;
    //cout<<"You are in a pineapple under the sea. Who are you (all lower case one word without pants)."<<endl;
        getline(cin, name);
        if (name == "spongebob")
        {

            cout<<"Congratulations! You now have the option to visit your friend patrick by typing 'under a rock' or sandy in a tree bubble by typing 'at the treedome'. Which would you like to do?"<<endl;
            string location;
            getline(cin,location);
            //cout<<location<<endl;
            if(location == "under a rock" || location == "at the treedome"){
                currentLoc = findLocation(location);
            }
            else{
                cout << "You can't go there. You lose a life." << endl;
            }
        }
    //cout<<"You are in a pineapple under the sea. Who are you (all lower case one word without pants)."<<endl;
    //getline(cin, name);
    while(name != "spongebob"){
        cout<<"You are in a pineapple under the sea. Who are you (all lower case one word without pants)."<<endl;
        getline(cin, name);
        if (name == "spongebob")
        {

            cout<<"Congratulations! You now have the option to visit your friend patrick by typing 'under a rock' or sandy in a tree bubble by typing 'at the treedome'. Which would you like to do?"<<endl;
            string location;
            getline(cin,location);
            //cout<<location<<endl;
            if(location == "under a rock" || location == "at the treedome"){
                currentLoc = findLocation(location);
            }
            else{
                cout << "You can't go there. You lose a life." << endl;
            }
        }
        else{
            livesT--;
            currentLoc->lives = livesT;
            //cout << currentLoc->lives << endl;

            if(currentLoc->lives == 0){
                Location *fail = new Location("fail", 1);
                currentLoc = fail;
                return currentLoc;
                //break;
            }
            else{
                cout << "Wrong! " << currentLoc->lives << " life left. Please try again." << endl;
            }
        }
    }

    return currentLoc;
}

Location* HashTable::rock(){
    Location *currentLoc = findLocation("under a rock");
    //currentLoc->visited = true;
    string name;
    while(name != "starfish"&&currentLoc->visited==false){
        cout<<"You are under a rock at your best friend Patrick's home. What type of fish is he (all lower case one word, hint: he's not a typical fish!)."<<endl;
        getline(cin, name);
        if (name == "starfish")
        {
            currentLoc->visited = true;
            if (allVisited() == true)
            {
                break;
            }

          string location;
            cout<<"Congratulations! You now have the option to go to work at the krusty krab by typing 'at the krusty krab' or sandy in a tree bubble by typing 'at the treedome'. Which would you like to do?"<<endl;
            getline(cin,location);
            //cout<<location<<endl;
            if(location == "at the krusty krab" || location == "at the treedome"){
                currentLoc = findLocation(location);
            }
            else{
                cout << "You can't go there. You lose a life." << endl;
            }
        }
        else{
            livesT--;
            currentLoc->lives = livesT;
            if(currentLoc->lives == 0){
                Location *fail = new Location("fail", 1);
                currentLoc = fail;
                return currentLoc;
                //break;
            }
            else{
                cout << "Wrong! " << currentLoc->lives << " life left. Please try again." << endl;
            }
        }
    }
    return currentLoc;
}
Location* HashTable::treedome(){
    Location *currentLoc = findLocation("at the treedome");
    //currentLoc->visited = true;
    string name;
    while(name != "squirrel"&&currentLoc->visited==false){
        cout<<"You are now in your friend sandy's treedome. What type of animal is sandy(all lower case one word, hint: they love acorns!)."<<endl;
        getline(cin, name);
        if (name == "squirrel")
        {
            currentLoc->visited = true;
            if (allVisited() == true)
            {
                break;
            }
            cout<<"Congratulations! You now have the option to go to the salty spitoon by typing 'at the salty spitoon' or visit your friend patrick by typing 'under a rock'. Which would you like to do?"<<endl;
            string location;
            getline(cin,location);
            //cout<<location<<endl;
            if(location == "at the salty spitoon" || location == "under a rock"){
                currentLoc = findLocation(location);
            }
            else{
                cout << "You can't go there. You lose a life." << endl;
            }
        }
        else{
            livesT--;
            currentLoc->lives = livesT;
            if(currentLoc->lives == 0){
                Location *fail = new Location("fail", 1);
                currentLoc = fail;
                return currentLoc;
                //break;
            }
            else{
                cout << "Wrong! " << currentLoc->lives << " life left. Please try again." << endl;
            }
        }
    }
    return currentLoc;
}
Location* HashTable::chumBucket(){
    Location *currentLoc = findLocation("at the chum bucket");
    //currentLoc->visited = true;
    string name;
    while(name != "computer"&&currentLoc->visited==false){
        cout<<"You are now at the chum bucket. What is plankton's wife (all lower case one word, hint: she's not a fish)."<<endl;
        getline(cin, name);
        if (name == "computer")
        {
            currentLoc->visited = true;
            if (allVisited() == true)
            {
                break;
            }
            cout<<"Congratulations! You now have the option to go to the salty spitoon by typing 'at the salty spitoon' or the krusty krab by typing 'at the krusty krab'. Which would you like to do?"<<endl;
            string location;
            getline(cin,location);
            //cout<<location<<endl;
            if(location == "at the salty spitoon" || location == "at the krusty krab"){
                currentLoc = findLocation(location);
            }
            else{
                cout << "You can't go there. You lose a life." << endl;
            }
        }
        else{
            livesT--;
            currentLoc->lives = livesT;
            if(currentLoc->lives == 0){
                Location *fail = new Location("fail", 1);
                currentLoc = fail;
                return currentLoc;
                //break;
            }
            else{
                cout << "Wrong! " << currentLoc->lives << " life left. Please try again." << endl;
            }
        }
    }

    return currentLoc;
}
Location* HashTable::krustyKrab(){
    Location *currentLoc = findLocation("at the krusty krab");
    //currentLoc->visited = true;
    string name;
    while(name != "frycook"&&currentLoc->visited==false){
        cout<<"You are now at the krusty krab. What is your job here (all lower case one word, hint: your neighbor squidward gives you orders from his boat)."<<endl;
        getline(cin, name);
        if (name == "frycook")

        {
            currentLoc->visited = true;
            if (allVisited() == true)
            {
                break;
            }
            cout<<"Congratulations! You now have the option to visit your boss mr. krabb's arch nemesis plankton's resturant the chum bucket by typing 'at the chum bucket' or visit your friend patrick by typing 'under a rock'. Which would you like to do?"<<endl;
            string location;
            getline(cin,location);
            //cout<<location<<endl;
            if(location == "under a rock" || location == "at the chum bucket"){
                currentLoc = findLocation(location);
            }
            else{
                cout << "You can't go there. You lose a life." << endl;
            }
        }
        else{
            livesT--;
            currentLoc->lives = livesT;
            if(currentLoc->lives == 0){
                Location *fail = new Location("fail", 1);
                currentLoc = fail;
                return currentLoc;
                //break;
            }
            else{
                cout << "Wrong! " << currentLoc->lives << " life left. Please try again." << endl;
            }
        }
    }

    return currentLoc;
}
Location* HashTable::saltySpitoon(){
    Location *currentLoc = findLocation("at the salty spitoon");
    //currentLoc->visited = true;
    string name;
    while(name != "tough"&&currentLoc->visited==false){
        cout<<"You are now at the salty spitoon. What are you required to be to enter (all lower case one word, hint: welcome to the salty spitoon, how ______ are ya?)."<<endl;
        getline(cin, name);
        if (name == "tough")
        {

            currentLoc->visited = true;
            if (allVisited() == true)
            {
                break;
            }
            string location;
            cout<<"Congratulations! You now have the option to visit your boss mr. krabb's arch nemesis plankton's resturant the chum bucket by typing 'at the chum bucket' or sandy in a tree bubble by typing 'at the treedome'. Which would you like to do?"<<endl;
            getline(cin,location);
            //cout<<location<<endl;
            if(location == "at the chum bucket" || location == "at the treedome"){
                currentLoc = findLocation(location);
            }
            else{
                cout << "You can't go there. You lose a life." << endl;
            }
        }
        else{
            livesT--;
            currentLoc->lives = livesT;
            if(currentLoc->lives == 0){
                Location *fail = new Location("fail", 1);
                currentLoc = fail;
                return currentLoc;
                //break;
            }
            else{
                cout << "Wrong! " << currentLoc->lives << " life left. Please try again." << endl;
            }
        }
    }
    return currentLoc;
}

//making changes


