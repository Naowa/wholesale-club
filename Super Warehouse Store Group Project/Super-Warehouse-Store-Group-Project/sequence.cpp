//V FINAL

#include "sequence.h"
#include <iostream>
#include <algorithm>

/**********************************************************
 *
 * Sequence - O(n)
 *_________________________________________________________
 * default ctr
 *_________________________________________________________
 * PRE-CONDITIONS
 * The following will need defined values
 * data: data array
 * capacity: capacity of arr
 * used: used of arr
 * current_index: current index of array
 *
 * POST-CONDITIONS
 * initializes the sequence
 **********************************************************/

Sequence::Sequence(): used(0), current_index(0), capacity(20)
{
    this->data = new valPtr[this->capacity];
    for(size_type i = 0; i < this->capacity; i++)
    {
        this->data[i] = NULL;                                             // Initialize all valPtrs to null;
    }
}

/**********************************************************
 *
 * ~Sequence - O(n)
 *_________________________________________________________
 * destructor
 *_________________________________________________________
 * PRE-CONDITIONS
 * The following will need defined values
 * data: data array
 *
 * POST-CONDITIONS
 * sequence is destroyed
 **********************************************************/

Sequence::~Sequence()
{
    delete []data;
}

/**********************************************************
 *
 * start - O(n)
 *_________________________________________________________
 * sets current index to 0
 *_________________________________________________________
 * PRE-CONDITIONS
 * The following will need defined values
 * data: data array
 * current_index: current index of arr
 * used: used of arr
 *
 * POST-CONDITIONS
 * n/a
 **********************************************************/

void Sequence::start()
{
    if (this->used != 0)
        this->current_index = 0;
    else
        this->data[current_index] = NULL;
}

/**********************************************************
 *
 * advance - O(n)
 *_________________________________________________________
 * increments current index
 *_________________________________________________________
 * PRE-CONDITIONS
 * The following will need defined values
 * current_index: current index of arr
 * used: used of arr
 *
 * POST-CONDITIONS
 * n/a
 **********************************************************/

void Sequence::advance()
{
    if (is_item())
        this->current_index++;
    else
        this->current_index = used;           // Set to the end...
}

/**********************************************************
 *
 * insert - O(n^2)
 *_________________________________________________________
 * inserts value in array at current index
 *_________________________________________________________
 * PRE-CONDITIONS
 * The following will need defined values
 * current_index: current index of arr
 * used: used of arr
 * capacity: capacity of arr
 * entry: pointer to a member
 *
 * POST-CONDITIONS
 * n/a
 **********************************************************/

// make sure insert is unique
void Sequence::insert(valPtr & entry)
{
    // Check for duplicates
    for (size_type i = 0; i < this->used; i++)
    {
        if (this->data[i]->GetId() == entry->GetId())
        {
            return;
        }
    }

    if (this->used >= this->capacity)
    {
        this->resize();
    }
    if (this->used < this->capacity) {
        if (!is_item()) {
            this->current_index = 0;
        }
        if (this->used > 0)
        {
            for (size_type i = this->used - 1; (i != -1) && (i >= this->current_index); i--)
            {
                this->data[i + 1] = this->data[i];
            }
        }
        this->data[current_index] = entry;
        this->used++;
    }
    else
        std::cout << "Over Capacity" << std::endl;
    this->sort();
}

/**********************************************************
 *
 * remove_current - O(n)
 *_________________________________________________________
 * removes value at current index
 *_________________________________________________________
 * PRE-CONDITIONS
 * The following will need defined values
 * current_index: current index of arr
 * used: used of arr
 * data: arr
 *
 * POST-CONDITIONS
 * n/a
 **********************************************************/

void Sequence::remove_current()
{
    if (is_item())
    {
        for (size_type i = current_index; i < used - 1; ++i)
        {
            this->data[i] = this->data[i + 1];
        }
        this->data[used - 1] = NULL;
        this->used--;
    }
    else
    {
        std::cout << "Not an item." << std::endl;
    }
}

/**********************************************************
 *
 * resize - O(n)
 *_________________________________________________________
 * doubles capacity of arr
 *_________________________________________________________
 * PRE-CONDITIONS
 * The following will need defined values
 * used: used of arr
 * capacity: cap of arr
 * data: arr
 *
 * POST-CONDITIONS
 * capacity is doubled
 **********************************************************/

void Sequence::resize()
{
    size_type newCap = 2 * this->capacity;
    size_type newUsed = this->capacity;
    Sequence::valPtr* tempData = new Sequence::valPtr[newCap];

    std::copy(this->data, this->data + this->used, tempData);

    delete[] data;
    this->data = tempData;
    this->capacity = newCap;
    this->used = newUsed;

    tempData = NULL;
}

/**********************************************************
 *
 * sort - O(n^2)
 *_________________________________________________________
 * sorts the array by id
 *_________________________________________________________
 * PRE-CONDITIONS
 * The following will need defined values
 * used: used of arr
 * data: arr
 *
 * POST-CONDITIONS
 * array is sorted
 **********************************************************/

void Sequence::sort()
{
    start();
    int lowest_ID;
    int lowestIndex;
    if (is_item())
    {
        for (size_type i = 0; i < this->used; i++)
        {
            lowest_ID = this->data[i]->GetId();
            lowestIndex = i;
            for (size_type j = i; j < this->used; j++)
            {
                if (this->data[j]->GetId() < lowest_ID)
                {
                    lowest_ID = this->data[j]->GetId();
                    lowestIndex = j;
                }
            }
            valPtr p = this->data[i];
            this->data[i] = this->data[lowestIndex];
            this->data[lowestIndex] = p;
        }
    }
}

/**********************************************************
 *
 * is_item - O(1)
 *_________________________________________________________
 * determines if an item is at current index
 *_________________________________________________________
 * PRE-CONDITIONS
 * The following will need defined values
 * used: used of arr
 * data: arr
 * current_index: current index of arr
 *
 * POST-CONDITIONS
 * n/a
 **********************************************************/

bool Sequence::is_item() const
{
    if (this->current_index >= this->capacity || this->current_index < 0)
        return false;
    if (this->current_index >= this->used)
        return false;
    if (this->data[current_index] == NULL)
        return false;
    else
        return true;
}

/**********************************************************
 *
 * current - O(1)
 *_________________________________________________________
 * returns pointer to current index
 *_________________________________________________________
 * PRE-CONDITIONS
 * The following will need defined values
 * data: arr
 * current_index: current index of arr
 *
 * POST-CONDITIONS
 * n/a
 **********************************************************/

Sequence::valPtr Sequence::current()
{
    if (is_item())
        return this->data[current_index];
    else
        return NULL;
}

/**********************************************************
 *
 * display - O(n)
 *_________________________________________________________
 * displays entire seq
 *_________________________________________________________
 * PRE-CONDITIONS
 * The following will need defined values
 * data: arr
 * current_index: current index of arr
 *
 * POST-CONDITIONS
 * n/a
 **********************************************************/

void Sequence::display()
{
       this->start();
       while(is_item())
       {
           std::cout << data[current_index]->GetId();
           this->advance();
       }
}

/**********************************************************
 *
 * operator [] - O(1)
 *_________________________________________________________
 * overloaded operator for []
 *_________________________________________________________
 * PRE-CONDITIONS
 * The following will need defined values
 * used: used of arr
 * data: arr
 * index: index searching for
 *
 * POST-CONDITIONS
 * n/a
 **********************************************************/

Sequence::valPtr Sequence::operator [] (size_type index)
{
    assert(index < this->used);
    return this->data[index];
}

/**********************************************************
 *
 * add_member - O(n)
 *_________________________________________________________
 * adds member to the seq
 *_________________________________________________________
 * PRE-CONDITIONS
 * The following will need defined values
 * used: used of arr
 * capacity: cap of arr
 * data: arr
 * entry: pointer to a member
 *
 * POST-CONDITIONS
 * n/a
 **********************************************************/

void Sequence::add_member(valPtr &entry)
{
        // Check for duplicates
        for (size_type i = 0; i < used; i++)
        {
            if (data[i]->GetId() == entry->GetId())
            {
                return;
            }
        }
        if ( (used + 1) > capacity ){
            resize();
        }
    data[used] = entry;
    used++;
}

/**********************************************************
 *
 * remove_member - O(n^2)
 *_________________________________________________________
 * removes member from the seq
 *_________________________________________________________
 * PRE-CONDITIONS
 * The following will need defined values
 * used: used of arr
 * data: arr
 * id: member's id
 *
 * POST-CONDITIONS
 * n/a
 **********************************************************/

void Sequence::remove_member(int id)
{
    for (int i = 0; i < this->used; i++){
        if (this->data[i]->GetId() == id){
            for (int j = i; j < (this->used - 1); j++){
                this->data[j] = this->data[j + 1];
            }
            this->used--;
        }
    }
}

/**********************************************************
 *
 * checkUpgrade - O(n)
 *_________________________________________________________
 * checks if member should upgrade
 *_________________________________________________________
 * PRE-CONDITIONS
 * The following will need defined values
 * used: used of arr
 * data: arr
 * id: member's id
 *
 * POST-CONDITIONS
 * n/a
 **********************************************************/

bool Sequence::checkUpgrade(int id)
{
    for (int i = 0; i < used; i++){
        if (data[i]->GetId() == id){

            //change GetType() to getType() ???
            if(data[i]->GetType() == wholesalegroup::basic)
            {
                double possibleRebate = data[i]->getAnnualTotal() * .05;
                if(possibleRebate > 15)
                {
                    //display in GUI here
                    return true;
                }
                //display in GUI here
                return false;
            }
            else
            {
//                std::cout << "ERROR. Check upgrade on preferred." << std::endl;
                return false;
            }

        }
    }

    //default is false
    return false;
}

/**********************************************************
 *
 * checkDowngrade - O(n)
 *_________________________________________________________
 * checks if member should downgrade
 *_________________________________________________________
 * PRE-CONDITIONS
 * The following will need defined values
 * used: used of arr
 * data: arr
 * id: member's id
 *
 * POST-CONDITIONS
 * n/a
 **********************************************************/

bool Sequence::checkDowngrade(int id)
{
    for (int i = 0; i < used; i++){
        if (data[i]->GetId() == id){

            if(data[i]->GetType() == wholesalegroup::preferred) // change to preferred after armen changes
            {
                double currentRebate = data[i]->getRebateAmount();
                if(data[i]->getAnnualTotal() - currentRebate < 15)
                {
                    //display in GUI here
                    return true;
                }
                //display in GUI here
                return false;
            }
            else
            {
//                std::cout << "ERROR. Check downgrade on basic." << std::endl;
                return false;
            }

        }
    }

    //default is false
    return false;
}

/**********************************************************
 *
 * find_user - O(n)
 *_________________________________________________________
 * finds user with id
 *_________________________________________________________
 * PRE-CONDITIONS
 * The following will need defined values
 * used: used of arr
 * data: arr
 * id: member's id
 *
 * POST-CONDITIONS
 * n/a
 **********************************************************/

int Sequence::find_user(int id)
{
    for (int i = 0; i < used; i++){
        if (data[i]->GetId() == id){
            return i;
        }
    }
    //error code -1 if not found
    return -1;
}

/**********************************************************
 *
 * find_user - O(n)
 *_________________________________________________________
 * finds user with name
 *_________________________________________________________
 * PRE-CONDITIONS
 * The following will need defined values
 * used: used of arr
 * data: arr
 * name: member's name
 *
 * POST-CONDITIONS
 * n/a
 **********************************************************/

int Sequence::find_user(string name)
{
    int count = 0;
    int found_index = 0;

        //count number of instances of name
        for (int i = 0; i < used; i++){
            if (data[i]->GetName() == name){
                count++;
                found_index = i;
            }
        }

        //if only 1 found, return i
        if (count == 1){
            return found_index;
        }
        //if more than 1, return error code -2
        if (count > 1){
            return -2;
        }
    //error code -1 if not found
    return -1;
}

/**********************************************************
 *
 * sortByPref - O(n^2)
 *_________________________________________________________
 * sorts members by pref
 *_________________________________________________________
 * PRE-CONDITIONS
 * The following will need defined values
 * capacity: cap of arr
 * current_index: current index of arr
 *
 * POST-CONDITIONS
 * n/a
 **********************************************************/

Sequence& Sequence::sortByPref()
{
	Sequence* prefSorted = new Sequence;

	prefSorted->current_index = this->current_index;
	prefSorted->capacity = this->capacity;

	start();
	// Fill preferred
	while (this->is_item())
	{
		wholesalegroup::Member* temp = current();
		if (current()->GetType() == wholesalegroup::preferred)
		{
			prefSorted->add_member(temp);
		}
		advance();
	}
	start();
	// Fill the basic
	while (this->is_item())
	{
		wholesalegroup::Member* temp = current();
		if (current()->GetType() == wholesalegroup::basic)
		{
			prefSorted->add_member(temp);
		}
		advance();
	}
	return *prefSorted;
}
