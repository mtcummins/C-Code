/* 
 * File:   Dictionary.cpp
 * Author: mtcummins
 * 
 * Created on March 31, 2019, 3:11 PM
 */

using namespace std;
#include "Dictionary.h"




Dictionary::Dictionary(){
    
}



void Dictionary::prompt(){
    cout << "Enter words, words may not contain spaces, type stop when done.";
    cout << "If no words are entered the dictionary will populate itself." << endl;
   
    readInConsole();
    if(dictionary.size()==0){
        readInFile();
    }
    
}   
void Dictionary::readInConsole(){
     string input;
     cin >> input;
     while (input != "done"){
        dictionary.push_back(input);
        cin >> input;
    }
}

void Dictionary::readInFile(){
    string fileName = "Dictionary.txt";
    ifstream infile(fileName);
    string input;
    
    if (!infile){
        cout << "Error Opening Input File " + fileName << endl;
        exit (-1);
    }
    
    infile >> input;
    while (!infile.eof()){
        dictionary.push_back(input);
        infile >> input;
    }
}

string Dictionary::randomWord(){
    int randomNumber;
    string ranWord;
    srand(time(0));
    randomNumber = rand() % dictionary.size() + 1;
    randomNumber = randomNumber - 1;
    ranWord = dictionary[randomNumber];
    return ranWord;
}

