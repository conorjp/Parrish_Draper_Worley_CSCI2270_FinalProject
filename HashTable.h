//
//  HashTable.h
//  
//
//  Created by Conor Parrish on 4/13/15.
//
//

#ifndef _HashTable_h
#define _HashTable_h

struct Location{
    std::string title;
    int lives;
    Location *next;
    
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
    Movie* findLocation(std::string in_title);
    void deleteLocation(std::string in_title);
    void printMap();
    int hashSum(std::string x);
  protected:
  private:
    std::vector<Location*> table;
    int tableSize = 10;
};

#endif
