/* 
 * File:   WordGuess.cpp
 * Author: mtcummins
 * 
 * Created on March 31, 2019, 3:11 PM
 */
using namespace std;
#include "WordGuess.h"

WordGuess::WordGuess() {
    
}



void WordGuess::start(){
    string start;
    cout << "welcome to the Word Guessing game" << endl;
    dictionary.prompt();
    
    cout << "Would you like to begin type start when ready." << endl;
    cin >> start;
    bool win=false;
    while (start == "start"){
        cout << "game is now starting"<< endl;
        CurrentGame newGame(dictionary.randomWord());
        win = newGame.startNewGame();
        if(win==true){
            cout << "You won the Game." << endl;
            cout << "The word was: " << newGame.getCurrentWord() << endl;
            timesWon++;
        }else{
            cout << "You Lost the Game." << endl;
            cout << "The word was: " << newGame.getCurrentWord() << endl;
            timesLost++;
        }
        
        cout<< endl << "Would you like to play again? If so type start, if not type anything else." << endl;
        cin >> start;  
    };
    
    endGame();
    
}   

void WordGuess::endGame(){
    cout << "Thank You For Playing." << endl;
    cout << "You have won " << timesWon << " times, and lost " << timesLost << " times."  << endl;
}


