//V FINAL

#ifndef SEQUENCE_H
#define SEQUENCE_H

#include <cstdlib>
#include <cassert>
#include "member.h"

using std::string;

class Sequence
{
public:
    typedef wholesalegroup::Member value_type;              //value_type - typedef a Member type
    typedef wholesalegroup::Member* valPtr;                 //valPtr - typedef for a Member pointer
    typedef std::size_t size_type;                          //size_type - typedef for a size_t
    Sequence();                                             //Sequence - default seq ctr
    ~Sequence();                                            //~Sequence - seq destructor
    void start();                                           //start - sets current index to 0
    void advance();                                         //advance - increments current index
    void insert(valPtr &entry);                             //insert - inserts an entry into seq
    void remove_current();                                  //remove_current - removes item at current index
    void resize();                                          //resize - doubles the capacity of the seq
    void sort();                                            //sort - sorts the seq
    bool is_item() const;                                   //is_item - determines if item at index exists
    valPtr current();                                       //current - returns pointer at current index
    void display();                                         //display - test function for displaying seq
    valPtr operator [] (size_type index);                   //operator - overloaded [] operator for accessing
    inline size_type size() const { return this->used; }    //size - returns used
    inline size_type Get_Capacity(){return this->capacity;} //Get_Capacity - returns capacity
    void add_member(valPtr &entry);                         //add_member - adds member to seq
    void remove_member(int id);                             //remove_member - removes member from seq
    int find_user(int id);                                  //find_user - finds user with id
    int find_user(string name);                             //find_user - finds user with name
    bool checkUpgrade(int id);                              //checkUpgrade - determines if member should upgrade
    bool checkDowngrade(int id);                            //checkDowngrade - determines if member should downgrade
    Sequence& sortByPref();                                 //sortByPref - sorts members by preferred
private:
    size_type capacity;                                     //capacity - capacity of seq
    valPtr* data;                                           //data - pointer to a member array
    size_type used;                                         //used - used of seq
    size_type current_index;                                //current_index - manages current index
};

#endif // SEQUENCE_H
