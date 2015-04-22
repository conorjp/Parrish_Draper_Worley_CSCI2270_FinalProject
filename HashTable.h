//
//  HashTable.h
//  
//
//  Created by Conor Parrish on 4/13/15.
//
//

#ifndef _HashTable_h
#define _HashTable_h

struct Movie{
    std::string title;
    int year;
    Movie *next;
    
    Movie(){};
    
    Movie(std::string in_title, int in_year)
    {
        title = in_title;
        year = in_year;
    }
    
};

class HashTable{
  public:
    HashTable();
    ~HashTable();
    void insertMovie(std::string in_title, int year);
    Movie* findMovie(std::string in_title);
    void deleteMovie(std::string in_title);
    void printInventory();
    int hashSum(std::string x);
  protected:
  private:
    std::vector<Movie*> table;
    int tableSize = 10;
};

#endif
