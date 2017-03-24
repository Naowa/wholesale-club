#include "sequence.h"
#include <iostream>
#include <algorithm>                   // used for copy. Again should we right our own?

using namespace std;

Sequence::Sequence(): used(0), current_index(0), capacity(20)
{
    data = new memPtr[capacity];
    for(size_type i = 0; i < capacity; i++)
    {
        data[i] = NULL;                                             // Initialize all memPtrs to null;
    }
}

Sequence::~Sequence()
{
    cout << "destructor called\n";
    delete []data;
}

void Sequence::start()
{
    if (used != 0)
        current_index = 0;
    else
        data[current_index] = NULL;			// Why do i need this again?
}

void Sequence::advance()
{
    if (is_item())
        current_index++;
    else
        current_index = used;           // Set to the end...
}

// make sure insert is unique
void Sequence::insert(memPtr & entry)
{
    // Check for duplicates
    for (size_type i = 0; i < used; i++)
    {
        if (data[i]->GetId() == entry->GetId())
        {
            return;
        }
    }

    if (used > capacity)
    {
        resize();
    }
    if (used < capacity) {
        if (!is_item()) {
            current_index = 0;
        }
        if (used > 0)
        {
            for (size_type i = used - 1; (i != -1) && (i >= current_index); i--)
            {
                data[i + 1] = data[i];
            }
        }
        data[current_index] = entry;
        used++;
    }
    else
        cout << "Over Capacity" << endl;
}

void Sequence::remove_current()
{
    if (is_item())
    {
//        std::cout<<current_index<<endl;
//        delete data[current_index];
        for (size_type i = current_index; i < used - 1; ++i)
        {
            data[i] = data[i + 1];
        }
        data[used - 1] = NULL;
        --used;
    }
    else
    {
        cout << "Not an item." << endl;					// maybe put something here later
    }
}

void Sequence::add_member(memPtr &entry)
{
        if ( (used + 1) > capacity ){
            resize();
        }
    data[used] = entry;
    used++;
}

void Sequence::remove_member(int id, string name)
{
    for (int i = 0; i < used; i++){
        if ( (data[i]->GetId() == id) && (data[i]->GetName() == name) ){
            for (int j = i; j < (used - 1); j++){
                data[j] = data[j + 1];
            }
            used--;
        }
    }
}

void Sequence::resize()
{
    size_type newCapacity = 2 * capacity;
    size_type newUsed = capacity;
    Sequence::memPtr* tempData = new Sequence::memPtr[newCapacity];

//    for (size_type i = 0; i < capacity; i++)
//    {
//        tempData[i] = data[i];
//    }
    copy(data, data + used, tempData);

    delete[] data;
    data = tempData;
    capacity = newCapacity;
    used = newUsed;
}

void Sequence::sort()
{
    start();
    int lowest_ID;
    int lowestIndex;
    if (is_item())
    {

        for (size_type i = 0; i < used; i++)
        {
            lowest_ID = data[i]->GetId();
            lowestIndex = i;
            for (size_type j = i; j < used; j++)
            {
                if (data[j]->GetId() < lowest_ID)
                {
                    lowest_ID = data[j]->GetId();
                    lowestIndex = j;
                }
            }
            memPtr p = data[i];
            data[i] = data[lowestIndex];
            data[lowestIndex] = p;
        }
    }

}

bool Sequence::is_item() const
{
    if (current_index >= capacity || current_index < 0)
        return false;

    if (data[current_index] == NULL)
        return false;
    else
        return true;
}

Sequence::memPtr Sequence::current()
{
    if (is_item())
        return data[current_index];
    else
        return NULL;						// Don't know if right for sure
}

void Sequence::display()
{
       start();
       while(is_item())
       {
           cout << data[current_index]->GetId();
           advance();
       }
 }

Sequence::memPtr Sequence::operator [] (size_type index)
{
    if (index < used){
//        cout << "class [] operator: " << data[index]->GetId() << endl;
        return data[index];
    }
}

Sequence::size_type Sequence::Get_Capacity()
{
    return capacity;
}

Sequence::size_type Sequence::Get_Used()
{
    return used;
}
