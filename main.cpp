#include <iostream>
#include <cctype> 
#include <fstream>
#include <string>
#include <cstdlib>
#include <cctype>     // Provides isdigit
#include <cstdlib>
#include <sstream>
#include <cstring>    // Provides strchr
#include "HashTableCh.h"
#include "HashNode.h"
#include " NodeStringList.h"

using namespace std;
using ClassProgram::HashTableCh;
using ClassProgram::NodeStringList;
using ClassProgram::HashNode;

// PROTOTYPES for functions
void EvaluateExpr(string& expr);
void StoreHash(stringstream& expr);
void AddNewScopeValue(string& varName);
void RemoveScopeValue();
HashNode* checkVar(string expr);
void processVar(HashNode* varName, stringstream& line);
void PrintLine(stringstream& line);
double Calculate(double& value, stringstream& line);
double GetValue(stringstream& line);


HashTableCh *hashTbl =  new HashTableCh();


//keeps track of scope
int currentScope;
//an array that holds varNames for each block
NodeStringList scopingBlockArray[25];

int iteration;


int main () {
    string line;

    currentScope = 0;
    iteration = 0;
    
    ifstream myfile ("example.txt");
    if (myfile.is_open())
    {
        while (getline(myfile,line) )
        {
           // cout << line << '\n';
            EvaluateExpr(line);
            
        }
        myfile.close();
    }
    
    else cout << "Unable to open file";
    
    return 0;
}

void EvaluateExpr(string& expr){
    string nextToken;
    
    //convert input string to a stream for parsing the expression
    stringstream line(expr);
    
    //continue to evaluate stream while the input is valid
    while (getline(line, nextToken, ' ')) {
      
        if (strcmp(nextToken.c_str(), "COM") == 0){
            break;
        }
        
        
        else if (strcmp(nextToken.c_str(), "VAR") == 0)
        {
            StoreHash(line);
            break;
            
        }
        
        else if (strcmp(nextToken.c_str(), "START") == 0)
        {
            currentScope++;
            break;
            
        }
        
        else if (strcmp(nextToken.c_str(), "PRINT") == 0)
        {
            PrintLine(line);
            break;
        }
        
        
        else if (strcmp(nextToken.c_str(), "FINISH") == 0)
        {
            //delete all the varNames in the scope
            //and in the hash table
            while (!scopingBlockArray[currentScope].isEmpty()){
                hashTbl->remove(scopingBlockArray[currentScope].remove());
            }
            currentScope--;
            break;
            
        }
        
        else if (checkVar(nextToken) != NULL) {
            cout << "Evaluating varName at EvaluateExpr: "<< nextToken << endl;
            processVar(checkVar(nextToken), line);
            break;
        
        }
        else
            ;
           // cout<<" The following variable doesn't exist \n";
    }
}

void StoreHash(stringstream& line){
    
    string nextToken;
    string varName;
    double value = 0;
    
    cout << "\n Calling StoreHash: \n";
    
    
    // 2 possibilities
    //either just variable declaration
    //or declaration plus the assignment
   // getline(line, nextToken, ' ');
   // varName = nextToken;
    
    //this while loop works as follows
    //getline creates a string token, if
    //the token is not "=" sign it means it's
    //a variable name. after the "=" sign is reached
    //the next value in the stream is stored in a double
    //the line stream should reach the end after this
    //and the loop exists
    while(getline(line, nextToken, ' ')){
       //  cout << "NextToken at iteration : "<<iteration++<<" "<<nextToken<<endl;
        
        
        if (strcmp(nextToken.c_str(), "=") != 0){
            varName = nextToken;
         //   cout << "An = sign NOT encountered, varName is now: " << varName << endl;
        }
        else {
       //     cout << "Encountered = sign, ";
            value= GetValue(line);
        //    cout << " value at StoreHash is:" << value << endl;
        }
    }
    hashTbl->insert(varName, value);
    
    //add the value to scope array, in order to keep track of scope
    AddNewScopeValue(varName);
    
}

void AddNewScopeValue(string& varName){
    
    scopingBlockArray[currentScope].insert(varName);
}

void RemoveScopeValue(){
    
    scopingBlockArray[currentScope].remove();
}

//check if variable exists
HashNode* checkVar(string varName){
  //  cout << "\n CheckVar was called:" << endl;
  //  cout << "The varName is: " << varName << endl;
    return hashTbl->find(varName);
}

void processVar(HashNode* varName, stringstream& line){
    
    string nextToken;
    double var;
    
    cout << "\n Calling ProcessVar: \n";
    
    
    
    // get the value of the variable
    var = varName->getValueData();
    
    //if next character in the stream is an operator
    //calculate the value
    if (strchr("+-/*%^", line.peek()) != NULL){
        var = Calculate(var, line);
        varName->setValueData(var);
    }
    //otherwise it's a unary operator or an assignment statement
    else
        while (getline(line, nextToken, ' ')) {
            
            if (strcmp(nextToken.c_str(), "++") == 0)
            {
                var++;
                varName->setValueData(var);
            }
            ;
            if (strcmp(nextToken.c_str(), "--") == 0)
            {
                var--;
                varName->setValueData(var);
            }
            
            //if the next token is equals sign
            //assign the number to variable
            if (strcmp(nextToken.c_str(), "=") == 0)
            {
                var = GetValue(line);
                varName->setValueData(var);
            }
            
        }
    
}

void PrintLine(stringstream& line){
    
    string nextToken;
    HashNode* variable;
    double value;
    
    //check if next variable is in the table
    //extract value from the variable
    //if there is no more on the line, print the variable
    //if there are more stuff perform necessary calculations
    getline(line, nextToken, ' ');
    if (checkVar(nextToken) == NULL)
        cout<<" The variable " <<nextToken <<" is undefined \n";
    else{
        variable = checkVar(nextToken);
        value = variable->getValueData();
        cout << nextToken << " IS ";

        while(line){
               if (strchr("+-/*%^", line.peek()) != NULL)
               {
                   value = Calculate(value, line);
               }
        }
    
    }
    
    cout << value <<endl;
     
    
 //   cout << "\n Calling PrintLine: \n";
    
    
  //  hashTbl->printList();
}


double Calculate(double& value, stringstream& line)
{
    double valueNext;
    char symbol;
    string token;
    
    //integer variables for the % and ^ operators
    int intValue1;
    int intValue2;
    
    //get the operator symbol
    getline(line, token, ' ');
    //convert string to char
    symbol = token[0];
   // cout << "The value of operator is:" << symbol << endl;
    
   // getline(line, token);
   // cout << "The value of last line is:" << token<< endl;
    
    //get the next value in the stream
    valueNext = GetValue(line);
   // valueNext = 0;
    
    switch (symbol)
    {
        case '+':
            value = value + valueNext;
            break;
        case '-':
            value = value - valueNext;
            break;
        case '*':
            value = value * valueNext;
            break;
        case '/':
            value = value / valueNext;
            break;
        case '%':
            intValue1 = value;
            intValue1 = valueNext;
            value = intValue1 % intValue2;
            break;
        case '^':
            intValue1 = value;
            intValue1 = valueNext;
            value = intValue1 ^ intValue2;
            break;
    }
    
    return value;

 }


double GetValue(stringstream& line){

    double value = 0;
   // bool done = false;
    HashNode* variable;
    string token;
    
    if(line && isdigit(line.peek())){
        line >> value;
        return value;
    }
    if(line && isalpha(line.peek())) {
      //  cout << "\n Calling GetValue, value is NOT a digit: /n";
        getline(line, token);
        variable = checkVar(token);
        
        if (variable != NULL) {
            value = variable->getValueData();
          //  cout << "The Value at GetValue is:" << value << endl;
        }
        else {
            cout<<"The variable "<< token <<" is undefined \n";
            exit(0);
        }
        
        return value;
    }
    
    return value;
    
}

