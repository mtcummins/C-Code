/* 
 * File:   WordGuess.h
 * Author: mtcummins
 *
 * Created on March 31, 2019, 3:11 PM
 */
#ifndef WORDGUESS_H
#define WORDGUESS_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Dictionary.h"
#include "CurrentGame.h"

class WordGuess {
private:
    int timesWon=0;
    int timesLost=0;
    Dictionary dictionary;
public:
    WordGuess();
    ~WordGuess(){};
    
    //this method starts the program for the word guessing game
    //pre: none
    //post: the variables for times won and lost should have values in them
    void start();
    
    //this the initial prompt that the users sees.
    //pre: none
    //post: none
    void prompt();
    
    //handles the output for the very end of the game where it prints out the
    //times won and lost
    //pre: none
    //Post: none
    void endGame();
};

#endif /* WORDGUESS_H */

