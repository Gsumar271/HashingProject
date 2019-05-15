//
//  NodeString.h
//  Hashing
//
//  Created by Eugene Sumaryev on 5/7/19.
//

#ifndef NodeString_h
#define NodeString_h

#include <cstdlib>  //
#include <set>      //
#include <string>
#include <iostream>

using namespace std;

namespace ClassProgram
{
    class NodeString
    {
    public:
        // MEMBER CONSTANTS
        typedef string valueType;
        
        // CONSTRUCTORS
        NodeString(valueType& initData, NodeString* initLink){data=initData; link=initLink;};
        ~NodeString(){};
        
        // MODIFICATION MEMBER FUNCTIONS
        void setData(valueType& newData){data = newData;}
        void setLink(NodeString* node){ link = node;}
        
        // CONSTANT MEMBER FUNCTIONS
        const valueType getData(){ return data; }
        NodeString* getLink() { return link; }
        
        
    private:
        valueType data;
        NodeString* link;
    };
    
    //FUNCTIONS FOR THE LIST
    void ListInsert(NodeString::valueType& entry,
                    NodeString*& headPtr)
    { headPtr = new NodeString(entry, headPtr); }
    
    void ListRemove(NodeString*& headPtr)
    {   NodeString *removePtr;
        removePtr = headPtr;
        headPtr = headPtr->getLink();
        delete removePtr; }
    
    
    
}


#endif /* NodeString_h */
