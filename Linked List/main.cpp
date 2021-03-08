/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: mtcummins
 *
 * Created on April 3, 2019, 2:53 PM
 */
#include <iostream>
#include <string>
#include <cstdlib>

#include "LinkedList.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    LinkedList myList;
    myList.RemoveTail();
    
    myList.AddHead(4);
    myList.Print(cout);
    myList.RemoveTail();
    myList.Print(cout);
    
    myList.AddHead(5);
    myList.AddTail(7);
    myList.Print(cout);
    
    return 0;
}

