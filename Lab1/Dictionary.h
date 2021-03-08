/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Dictionary.h
 * Author: mtcummins
 *
 * Created on March 31, 2019, 3:11 PM
 */

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
class Dictionary {
    private:
        vector <string> dictionary;
    public:
        Dictionary();
        ~Dictionary(){};
        
        // this method prompts the user for an input of words.
        // pre: none
        // post: none
        void prompt();
        
        // this method handles the population of the dictionary by the console
        // pre: none
        // post: the dictionary may be populated with words.
        void readInConsole();
        
        // this method handles the population of the dictionary by a file called
        // Dictionary.txt
        // pre: none
        // post: the dictionary may be populated with words.
        void readInFile();
        
        //  // this method handles the population of the dictionary by the console
        // pre: none
        // post: a random word is generated
        string randomWord();
        
};

#endif /* DICTIONARY_H */

