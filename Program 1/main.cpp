#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;
#include "course.h"

int loaddata(ifstream& infile, int nums[], int size);
// pre: 1st parameter must be a file of no more than 20 integers
//      3rd parameter must be size of 2nd parameter
// post: Data has been read from the input file represented
//       by the 1st parameter and loaded into the 2nd parameter
//       The number of values read is returned.

void loaddata2(ifstream& infile, vector<int>& vnums);	
// pre: 1st parameter must be a file of integers
// post: Data has been read from the input file represented
//       by the 1st parameter and loaded into the 2nd parameter

int main() {
    string fname;
    int numbers[20];
    vector<int> vnumbers;

    cout << "Enter file name: " << endl;
    cin >> fname;
    ifstream infile(fname); //older versions of C++ would require fname.c_str()
    if (!infile){
        cout << "Error Opening Input File " + fname << endl;
        exit (-1);
    }
    int count = loaddata(infile, numbers, 20);
    cout << "Array of Numbers" << endl;
    for (int i=0; i<count; i++){
        cout << (i+1) << ": " << numbers[i] << endl;
    }
    infile.close();
   

    infile.open(fname);
    if (!infile){
        cout << "Error Opening Input File " + fname << endl;
        exit (-1);
    }
    loaddata2(infile, vnumbers);
    cout << "Vector of Numbers" << endl;
    for (int i=0; i<vnumbers.size(); i++){  
        cout << (i+1) << ": " << vnumbers[i] << endl;
    }
    infile.close();
    
    Course c("Data Structures");
    cout << c.getName();
    
    
    return 0;
}
int loaddata(ifstream& infile, int nums[], int size){
	int number;
	int slot = 0;
	infile >> number;
	while (!infile.eof() && slot < size){
		nums[slot] = number;
		infile >> number;
		slot++;
	}
	return slot;
}

void loaddata2(ifstream& infile, vector<int>& vnums){
	int number;
	infile >> number;
	while (!infile.eof()){
            vnums.push_back(number);
            infile >> number;
	}
}
