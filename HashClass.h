//
//  HashClass.h
//  Hashing
//
//  Created by Eugene Sumaryev on 4/21/19.
//  Copyright © 2019 com.eugene. All rights reserved.
//

#ifndef HashClass_h
#define HashClass_h
#include <cstdlib>    //

namespace ClassProgram
{
    class HashClass
    {
    public:
        
        // TYPEDEF
        typedef double RecordType;
        // MEMBER CONSTANT
        static const std::size_t CAPACITY = 27;
        
        
        // CONSTRUCTOR
        HashClass();
        
        // MODIFICATION MEMBER FUNCTIONS
        void insert(const RecordType& entry);
        void remove(int key);
        
        // CONSTANT MEMBER FUNCTIONS
        bool isPresent(int key) const;
        void find(int key, bool& found, RecordType& result) const;
        std::size_t size() const { return used; }
        
    private:
        // MEMBER CONSTANTS -- These are used in the key field of special records.
        static const int NEVER_USED = -1;
        static const int PREVIOUSLY_USED = -2;
        
        // MEMBER VARIABLES
        RecordType data[CAPACITY];
        std::size_t used;
        
        // HELPER FUNCTIONS
        std::size_t hash(int key) const;
        std::size_t nextIndex(std::size_t index) const;
        void findIndex(int key, bool& found, std::size_t& index) const;
        bool neverUsed(std::size_t index) const;
        bool isVacant(std::size_t index) const;
    };
}


#endif /* HashClass_h */
