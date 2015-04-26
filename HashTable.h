//
//  HashTable.h
//
//  Final Project
//  CSCI-2270
//  Conor Parrish, James Draper, Luke Worley
//

#ifndef _HashTable_h
#define _HashTable_h

struct Location{
    std::string title;
    int lives;
    Location *next;
    Location *orderVisited;
    bool visited;

    Location(){};

    Location(std::string in_title, int in_lives)
    {
        title = in_title;
        lives = in_lives;
    }

};

class HashTable{
  public:
    HashTable();
    ~HashTable();
    void insertLocation(std::string in_title, int year);
    Location* findLocation(std::string in_title);
    void deleteLocation(std::string in_title);
    void printMap();
    void printPreviousLocations(Location *head);
    void printNotVisitedLocations(Location *head);
    int hashSum(std::string x);
    void setHealth(std::string name);
    void addToOrder (std:: string location);
    bool allVisited();
    Location* pineapple();
    Location* rock();
    Location* chumBucket();
    Location* krustyKrab();
    Location* saltySpitoon();
    Location* treedome();
  protected:
  private:
    std::vector<Location*> table;
    int tableSize = 5;
    Location *head;
};

#endif
