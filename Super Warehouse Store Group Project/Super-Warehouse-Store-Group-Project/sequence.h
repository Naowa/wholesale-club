// version 0.1.3
// SEQUENCE CLASS FOR OUR SUPER WAREHOUSE PROJECT

//UPDATE NOTES:
//New functions are indicated below/functions that were changed
//operator [] was fixed, assertion was incorrect
//add_member was updated with a newer version, checks for duplicates and sorts
//remove_member is the same, unchanged

#ifndef SEQUENCE_H
#define SEQUENCE_H

#include <cstdlib>                                     // provides size_t
#include <cassert>                                    // for assert
#include "member.h"

using std::string;

class Sequence
{
public:
    typedef wholesalegroup::Member value_type;                    // define member as value type
    typedef wholesalegroup::Member* valPtr;                          // used for pointers, the other is for the value
    typedef std::size_t size_type;                                            // defines the size type used in capacity. Non zero

    // CONSTRUCTOR
    Sequence();      // Constructor
    ~Sequence();

    // MODIFICATION FUNCITONS
    void start();                                               // Sets the current_index to 0
    void advance();                                         // Advances the current_index + 1
    void insert(valPtr &entry);                          // Inserts the

    void remove_current();

    void resize();
    void sort();

    // CONSTANT MEMBER FUNCTIONS

    bool is_item() const;                                   // whether the item at current_index exists
    valPtr current();                                          // returns the pointer to item at the current_index

    void display();                                            // Display for test only

    // OPERATOR OVERLOAD
    valPtr operator [] (size_type index);

    // ACCESSORS
    inline size_type size() const { return this->used; }
    inline size_type Get_Capacity(){return this->capacity;}


    ///***NEW FUNCTIONS IN THIS VERSION
    void add_member(valPtr &entry);
    void remove_member(int id);
    int find_user(int id);
    int find_user(string name);

    //***DAMON'S GROUP CHECK UPGRADE AND DOWNGRADE MOVED HERE
    bool checkUpgrade(int id);
    bool checkDowngrade(int id);

    ///***END OF NEW FUNCTIONS IN THIS VERSION

private:
    size_type capacity;
    valPtr* data;
    size_type used;                                         // variable unique to sequence
    size_type current_index;                            // variable unique to sequence
};

#endif // SEQUENCE_H
