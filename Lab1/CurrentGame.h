/* 
 * File:   CurrentGame.h
 * Author: mtcummins
 *
 * Created on March 31, 2019, 3:14 PM
 */

#ifndef CURRENTGAME_H
#define CURRENTGAME_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <string>


class CurrentGame {
    private:
        string currentWord;
        vector <char> wordProgress;
        vector <string> wordsGuessed;
        vector <string> lettersGuessed;
        int guessesLeft=0;
        bool correctWord = false;
    public:
        // this is the constructor for the current game class it takes in a random word
        // from the dictionary, and sets that as  the current word being played.
        CurrentGame();
        CurrentGame(string);
        ~CurrentGame(){};
        
        //this is what starts and controls the current game that is being played.
        //pre: dictionary is filled.
        //post: returns a boolean on whether the game was won or not.
        bool startNewGame();
        
        // this method displays the current state of the game including the, the number
        // of guesses left, words and letters guessed, as well as the current progress
        // of the guessed word.
        //pre: none
        //post: none 
        void displayState();
        
        // this method handles checking if the correct word was guessed
        //pre: there was a word guessed
        //post: sets the corroctWord variable to true if it was guessed.
        void correctWordGuessed(string);
        
        // this method handles whether all the letters of the word have been guessed.
        //pre: letters have been inputed    
        //post: sets the corroctWord variable to true if all letters where guessed.
        void allLettersGuessed();
       
        // this method handles the guessing of either letters or words.
        //pre: a word or a letter was guessed.
        //post: the vectors for words and letters guessed haven been updated
        void wordGuess();
        
        //gets the current word that is trying to be guessed.
        //pre: has a word set as current word   
        //post: none
        string getCurrentWord();
};

#endif /* CURRENTGAME_H */

