/*
Skeleton code for storage and buffer management
*/

#include <string>
#include <ios>
#include <fstream>
#include <vector>
#include <string>
#include <string.h>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <cmath>
#include "classes.h"
using namespace std;


int main(int argc, char* const argv[]) {

    // Create the EmployeeRelation file from Employee.csv
    StorageBufferManager manager("EmployeeRelation");
    manager.createFromFile("Employee.csv");
    
    // Loop to lookup IDs until user is ready to quit
    
    /*

    string mytest;
    string mydata = "(2$12345678$12345678)";
    string myindex;
    int runningDataOffset = 0;
    int runningIndexOffset = 0;
    int blockSize = 100;
    
    //initialize the buffer
    mytest.append(blockSize, ' ');
    
    do{
    
      //determine the size changes that would be required
      myindex = "[****,***]";
      myindex.replace(1, to_string(runningDataOffset).length(), to_string(runningDataOffset));
      myindex.replace(6, to_string(mydata.length()).length(), to_string(mydata.length()));
      //myindex = "[" + to_string(runningDataOffset) + "," + to_string(mydata.length()) + "]";
      runningDataOffset = runningDataOffset + mydata.length();
      runningIndexOffset = runningIndexOffset + myindex.length();
      
      //execute if possible, otherwise break
      if((runningDataOffset + runningIndexOffset) <= blockSize){
        mytest.replace(runningDataOffset - mydata.length(), mydata.length(), mydata);
        
        //send the padded index into the buffer
        mytest.replace(blockSize - runningIndexOffset, myindex.length(), myindex);
      }
      else{
        cout << "ran out of room" << endl;
        break;
      }
      
      
    } while(true);
    
    cout << mytest << endl;
    
    cout << mytest.length() << endl; 
    
    */

    return 0;
}
