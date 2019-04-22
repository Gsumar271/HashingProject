//
//  HashTable.cpp
//  Hashing
//
//  Created 4/20/19.
//

#include <stdio.h>
#include <cstdlib>
#include "HashTable.h"

namespace ClassProgram
{
    const std::size_t HashTable::CAPACITY;
    
    const int HashTable::NOT_USED;
    
    HashTable::HashTable()
    {
        std::size_t i;
        
        used = 0;
        
        //initialize all entries as NOT_USED
        for (i = 0; i < CAPACITY; ++i)
            data[i] = NOT_USED;  // Indicates a spot that's not been used.
        
    }
    
    void HashTable::insert(const RecordType& entry)
    //
    {
        std::size_t index;        // data[index] is location for the new entry
        
    
        // If the key wasn't already there, then find the location for the new entry.
        if (find(entry) == -1)
        {
            index = hash(entry);
            while (data[index] != NOT_USED)
                index = nextIndex(index);
            ++used;

        }
        else
            index = find(entry); //otherwise replace the old entry
    
        data[index] = entry;
        
        
    }

    
    //function that returns the index of the element if it's present
    //or -1 otherwise
    int HashTable::find(int key) const
    //
    {
        int found;
        int index;
        std::size_t count; // Number of entries that have been examined
        
        count = 0;
        index = hash(key);
        
        //check every entry
        while((count < CAPACITY) && (data[index] != key))
        {
            ++count;
            index = nextIndex(index);
        }

        if ((data[index] == key))
            found = index;
        else
            found = -1;

        return found;
    }
    
    //helper function that does the hashing
    inline int HashTable::hash(int key) const
    {
        return (key % CAPACITY);
    }

    //helper function to find the location of next index in the array
    inline int HashTable::nextIndex(std::size_t index) const
    //
    {
        return ((index+1) % CAPACITY);
    }
   
}
