//
//  HashClass.cpp
//  Hashing
//
//  Created by Eugene Sumaryev on 4/21/19.
//  Copyright © 2019 com.eugene. All rights reserved.
//

#include <stdio.h>
#include <cstdlib>
#include "HashClass.h"

namespace ClassProgram
{
    const std::size_t HashClass::CAPACITY;
    
    const int HashClass::NEVER_USED;
    
    const int HashClass::PREVIOUSLY_USED;
    
    HashClass::HashClass()
    {
        std::size_t i;
        
        used = 0;
        for (i = 0; i < CAPACITY; ++i)
            data[i] = NEVER_USED;  // Indicates a spot that's never been used.
    }
    
    void HashClass::insert(const RecordType& entry)
    //
    {
        bool alreadyPresent;   // True if entry.key is already in the table
        std::size_t index;        // data[index] is location for the new entry
        
        
        // Set index so that data[index] is the spot to place the new entry.
        findIndex(entry, alreadyPresent, index);
        
        // If the key wasn't already there, then find the location for the new entry.
        if (!alreadyPresent)
        {
            index = hash(entry);
            while (!isVacant(index))
                index = nextIndex(index);
            ++used;
        }
        
        data[index] = entry;
    }
    
    void HashClass::remove(int key)
    //
    {
        bool found;        // True if key occurs somewhere in the table
        std::size_t index;   // Spot where data[index].key == key
        
        
        findIndex(key, found, index);
        if (found)
        {   // The key was found, so remove this record and reduce used by 1.
            data[index] = PREVIOUSLY_USED; // Indicates a spot that's no longer in use.
            --used;
        }
    }
    
    bool HashClass::isPresent(int key) const
    //
    {
        bool found;
        std::size_t index;
        
        
        findIndex(key, found, index);
        return found;
    }
    
    void HashClass::find(int key, bool& found, RecordType& result) const
    //
    {
        std::size_t index;
        
        
        findIndex(key, found, index);
        if (found)
            result = data[index];
    }
    
    inline std::size_t HashClass::hash(int key) const
    {
        return (key % CAPACITY);
    }
    
    inline std::size_t HashClass::nextIndex(std::size_t index) const
    //
    {
        return ((index+1) % CAPACITY);
    }
    
    void HashClass::findIndex(int key, bool& found, std::size_t& i) const
    //
    {
        std::size_t count; // Number of entries that have been examined
        
        count = 0;
        i = hash(key);
        while((count < CAPACITY) && (data[i] != NEVER_USED) && (data[i] != key))
        {
            ++count;
            i = nextIndex(i);
        }
        found = (data[i] == key);
    }
    
    inline bool HashClass::neverUsed(std::size_t index) const
    {
        return (data[index] == NEVER_USED);
    }
    
    inline bool HashClass::isVacant(std::size_t index) const
    {
        return (data[index] == NEVER_USED) || (data[index] == PREVIOUSLY_USED);
    }
}
