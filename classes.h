#include <string>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <bitset>
using namespace std;

class Record {
public:
    int id, manager_id;
    std::string bio, name;

    Record(vector<std::string> fields) {
        id = stoi(fields[0]);
        name = fields[1];
        bio = fields[2];
        manager_id = stoi(fields[3]);
    }

    void print() {
        cout << "\tID: " << id << "\n";
        cout << "\tNAME: " << name << "\n";
        cout << "\tBIO: " << bio << "\n";
        cout << "\tMANAGER_ID: " << manager_id << "\n";
    }
};


class Page {
public:

  string buffer;
  int runningDataOffset;
  int runningIndexOffset;

};


class StorageBufferManager {

private:
    
    const int BLOCK_SIZE = 4096; // initialize the block size allowed in main memory according to the question 

    // You may declare variables based on your need 
    int curRecordLength;
    int curSlotDirAdd;
    Page page1block;
    string myindex;
    string mydata;

    void dumpPages(){
    
        cout << "Dumping pages" << endl;

        //open the data file
        ofstream outFile;
        outFile.open("EmployeeRelation.dat", ofstream::out|ofstream::app);
          
        //write the 3 buffers into the file
        outFile << page1block.buffer;
          
        //clear buffers and reset variables
        page1block.buffer.clear();
        page1block.runningDataOffset = 0;
        page1block.runningIndexOffset = 0;
        page1block.buffer.append(BLOCK_SIZE, ' ');
        
        //close the outfile
        outFile.close();

        cout << "Done dumping" << endl;
    }

    // Insert new record 
    void insertRecord(Record record) {
    
        //used to determine if the record finds a spot or not
    
        if(numRecords == 0){
          //initialize the buffers
          page1block.runningDataOffset = 0;
          page1block.runningIndexOffset = 0;
          page1block.buffer.append(BLOCK_SIZE, ' ');

        }
    
        numRecords++;
        cout << numRecords << endl;

        //build the record string
        mydata = "4$" + to_string(record.id) + "$" + record.name + "$" + record.bio + "$" + to_string(record.id) + "$";
        
        //build the padded string for the slot directory
        myindex = "[****,***]";
        myindex.replace(1, to_string(page1block.runningDataOffset).length(), to_string(page1block.runningDataOffset));
        myindex.replace(6, to_string(mydata.length()).length(), to_string(mydata.length()));

        //determine how much this new record/slot will increase the data/index offsets
        page1block.runningDataOffset = page1block.runningDataOffset + mydata.length();
        page1block.runningIndexOffset = page1block.runningIndexOffset + myindex.length();
        
        if((page1block.runningDataOffset + page1block.runningIndexOffset) <= BLOCK_SIZE){

          //send the data into the buffer
          page1block.buffer.replace(page1block.runningDataOffset - mydata.length(), mydata.length(), mydata);

          //send the padded index into the buffer
          page1block.buffer.replace(BLOCK_SIZE - page1block.runningIndexOffset, myindex.length(), myindex);
            
        } 
        //if our new record could not find a free spot, send the page to the data file and clear it to make room for the homeless record
        else{
          
          dumpPages();
          
          //put the record that just came in at the first position in the new block

          //build the record string
          mydata = "4$" + to_string(record.id) + "$" + record.name + "$" + record.bio + "$" + to_string(record.id) + "$";
          
          //build the padded string for the slot directory
          myindex = "[****,***]";
          myindex.replace(1, to_string(page1block.runningDataOffset).length(), to_string(page1block.runningDataOffset));
          myindex.replace(6, to_string(mydata.length()).length(), to_string(mydata.length()));

          //determine how much this new record/slot will increase the data/index offsets
          page1block.runningDataOffset = page1block.runningDataOffset + mydata.length();
          page1block.runningIndexOffset = page1block.runningIndexOffset + myindex.length();

          //send the data into the buffer
          page1block.buffer.replace(page1block.runningDataOffset - mydata.length(), mydata.length(), mydata);

          //send the padded index into the buffer
          page1block.buffer.replace(BLOCK_SIZE - page1block.runningIndexOffset, myindex.length(), myindex);
          
        }

    }

public:

    int numRecords = 0;
    

    StorageBufferManager(string NewFileName) {
        
        //initialize your variables
        FILE* relationFile; 

        // Create your EmployeeRelation file
        ofstream outFile;
        outFile.open(NewFileName + ".dat");
        outFile.close();

        
    }

    // Read csv file (Employee.csv) and add records to the (EmployeeRelation)
    void createFromFile(string csvFName) {
        
        //open the input file
        ifstream inputFile;
        inputFile.open(csvFName);

        //start reading from the file
        string curLine;
        string id;
        string manid;
        string name;
        string bio;

        //loop until all records have been sent to the insert function
        while(true){
            
            //process the id element
            if(getline(inputFile, curLine, ',')){
                id = curLine;
                
                //process the name element
                getline(inputFile, curLine, ',');
                name = curLine;
    
                //process the bio element
                getline(inputFile, curLine, ',');
                bio = curLine;
    
                //process the manager id element
                getline(inputFile, curLine);
                manid = curLine;
    
                //cout << id << " " << name << " " << bio << " " << manid << endl;
                
                vector<string> myVector{id, name, bio, manid};
                Record myRecord(myVector);
    
                //send the record to insertRecord
                insertRecord(myRecord);
                
            }
            //if the getline is invalid, that means there is no new line, break out and close the input file
            else{
                
                //if we're at the end of the input file, dump the currnt pages into the EmployeeRelation file
                dumpPages();
                
                break;
            }

        }

        //close the input file
        inputFile.close();

    }

    // Given an ID, find the relevant record and print it
    Record findRecordById(int id) {
        
        //grab 3 pages from the file and search them, if unsuccessful, loop

    }
};
