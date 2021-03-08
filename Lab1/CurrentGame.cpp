/* 
 * File:   CurrentGame.cpp
 * Author: mtcummins
 * 
 * Created on March 31, 2019, 3:14 PM
 */


using namespace std;
#include "CurrentGame.h"




CurrentGame::CurrentGame(string newWord):currentWord(newWord){
   
}


bool CurrentGame::startNewGame(){
    for(int i=0;i<currentWord.size();i++){
        wordProgress.push_back('-');
    }
    
    guessesLeft = currentWord.size();
    
    while(guessesLeft!=0&&correctWord!=true){
        displayState();
        wordGuess();
        guessesLeft--;
        
    }
    return correctWord;
}


void CurrentGame::displayState(){
    cout << endl << endl;
    cout << "Word Guess Game" << endl;
    cout << "Current word to guess:" << endl;
    
    for (int i=0; i < currentWord.size();i++){
        cout<<wordProgress[i];
    }
    cout << endl;
    
    cout << "You have " << guessesLeft << " guesses left." << endl;
            
           
    cout << "Letters Guessed:" << endl;
    if (lettersGuessed.size()!=0){
        for (int i=0; i < lettersGuessed.size();i++){
            if(i!=lettersGuessed.size()-1){
                cout << lettersGuessed[i] << ", ";
            }else {
                cout << lettersGuessed[i];
            }
        }
        cout << endl;
    }
    
    cout << "Words Guessed:" << endl;
    if (wordsGuessed.size()!=0){
        for (int i =0;i<wordsGuessed.size();i++){
           if(i!=wordsGuessed.size()-1){
                cout << wordsGuessed[i] << ", ";
            }else {
                cout << wordsGuessed[i];
            }
        }
        cout << endl;
    }
    
}

void CurrentGame::wordGuess(){
    string guess;
    cout << "please type in a LETTER, or try to guess the WORD." << endl;
    cin >> guess;
    if (guess.size()==1){        
        lettersGuessed.push_back(guess);       
        for(int i=0;i<currentWord.size();i++){
            if(currentWord.at(i) == guess.at(0)){
                wordProgress[i]=guess.at(0);
                allLettersGuessed();
            }
        }
    }else{
        wordsGuessed.push_back(guess);
        correctWordGuessed(guess);
    }
    
}


void CurrentGame::correctWordGuessed(string guess){
    if(guess == currentWord){
        correctWord = true;
    }else{
        correctWord = false;
    }
}


void CurrentGame::allLettersGuessed(){
    
    bool correct = true;
    int i=0;
    while(correct&&i<wordProgress.size()){
        if(wordProgress[i]=='-'){
            correct = false;
        }
        i++;
    }
    
    if (correct==1){
        correctWord=correct;
    }
}


string CurrentGame::getCurrentWord(){
    return currentWord;
}


