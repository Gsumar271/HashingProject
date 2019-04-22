//
//  HashTable.h
//  Hashing
//
//  Created on 4/20/19
//

#ifndef HashTable_h
#define HashTable_h
#include <cstdlib>    //

namespace ClassProgram
{
    class HashTable
    {
    public:
        
        // TYPEDEF
        typedef int RecordType;
        // MEMBER CONSTANT
        static const std::size_t CAPACITY = 27;
        
        
        // CONSTRUCTOR
        HashTable();
        
        // MODIFICATION MEMBER FUNCTIONS
        void insert(const RecordType& entry);
        
        // CONSTANT MEMBER FUNCTIONS
        int find(int key) const;
        std::size_t size() const { return used; }
        
    private:
        // MEMBER CONSTANTS
       static const int NOT_USED = -1;
        
        // MEMBER VARIABLES
        RecordType data[CAPACITY];
        std::size_t used;
        
        // HELPER FUNCTIONS
        int hash(int key) const;
        int nextIndex(std::size_t index) const;

    };
}

#endif /* HashTable_h */
