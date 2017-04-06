// version 0.1.5
#include "sequence.h"
#include <iostream>
#include <algorithm>                   // used for copy. Again should we right our own?

Sequence::Sequence(): used(0), current_index(0), capacity(20)
{
    this->data = new valPtr[this->capacity];
    for(size_type i = 0; i < this->capacity; i++)
    {
        this->data[i] = NULL;                                             // Initialize all valPtrs to null;
    }
}

Sequence::~Sequence()
{
    delete []data;
}

void Sequence::start()
{
    if (this->used != 0)
        this->current_index = 0;
    else
        this->data[current_index] = NULL;			// Why do i need this again?
}

void Sequence::advance()
{
    if (is_item())
        this->current_index++;
    else
        this->current_index = used;           // Set to the end...
}

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
        std::cout << "Not an item." << std::endl;					// maybe put something here later
    }
}

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

Sequence::valPtr Sequence::current()
{
    if (is_item())
        return this->data[current_index];
    else
        return NULL;						// Don't know if right for sure
}

void Sequence::display()
{
       this->start();
       while(is_item())
       {
           std::cout << data[current_index]->GetId();
           this->advance();
       }
 }

Sequence::valPtr Sequence::operator [] (size_type index)
{
    assert(index < this->used);
    return this->data[index];
}

///**NEW FUNCTIONS IN THIS VERSION
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
    // sort();                                      // Kit : "I had to remove this. Will explain eslewhere."
}

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
                std::cout << "ERROR. Check upgrade on preferred." << std::endl;
                return false;
            }

        }
    }

    //default is false
    return false;
}

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
                std::cout << "ERROR. Check downgrade on basic." << std::endl;
                return false;
            }

        }
    }

    //default is false
    return false;
}

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
///**END OF NEW FUNCTIONS IN THIS VERSION

///**NewFunction from version 0.1.5
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
//** End of new function from version 0.1.5
