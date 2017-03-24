// SEQUENCE CLASS FOR OUR SUPER WAREHOUSE PROJECT
// *NOTE : Ask group if we want to build our own copy function?!?

#ifndef SEQUENCE_H
#define SEQUENCE_H

#include <cstdlib>                                     // provides size_t
#include <cassert>                                    // for assert
#include "member.h"

#include <iostream>
using namespace std;

class Sequence
{
public:
    typedef wholesalegroup::Member value_type;                   // define member as value type
    typedef wholesalegroup::Member* memPtr;                     // used for pointers, the other is for the value
    typedef std::size_t size_type;                 // defines the size type used in capacity. Non zero

    // CONSTRUCTOR
    Sequence();      // Constructor
    ~Sequence();

    // MODIFICATION FUNCITONS
    void start();                                           // Sets the current_index to 0
    void advance();                                     // Advances the current_index + 1
    void insert(memPtr &entry);                    // Inserts the

    ////**andy added
    void add_member(memPtr &entry);
    void remove_member(int id, string name);
    ///*****



    void remove_current();

    void resize();
    void sort();

    // CONSTANT MEMBER FUNCTIONS
    inline size_type size() const { return used; }
    bool is_item() const;                             // whether the item at current_index exists
    memPtr current();                   // returns the item at the current_index. SHOULD THIS BE pointer or value?

    // Display for test only
    void display();

    // OPERATOR OVERLOAD
    memPtr operator [] (size_type index);
//    void operator+=(const Sequence& addend);            // DO I NEED THIS?!?
//    Sequence  operator+ (const Sequence& addend);     // DO I NEED THIS TOO?!
//    value_type operator[] (size_type index) const;         // *note to check this again. Might need more

    // ACCESSORS
    size_type Get_Capacity();
    size_type Get_Used();
    memPtr* data;

private:
    size_type capacity;   // Don't know if i need this or not? I want to change
//    memPtr* data;
    size_type used;                                     // variable unique to sequence
    size_type current_index;                        // variable unique to sequence
};

#endif // SEQUENCE_H
