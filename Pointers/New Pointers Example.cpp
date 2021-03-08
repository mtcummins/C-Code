/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: mtcummins
 *
 * Created on May 31, 2019, 2:49 PM
 */

#include <cstdlib>
#include <string>
#include <iostream>
#include <string.h>
using namespace std;

//this is called smart pointers

class IntPtr{
private: 
    int* _ptr;
public:
    IntPtr(){
        _ptr = nullptr;
    }
    
    ~IntPtr(){
        delete _ptr;
    }
    
    IntPtr(int x){
        _ptr = new int(x);
    }
    
    int getInt(){
        return *_ptr;
    } 
    
    int& operator*(){
        return *_ptr;
    }
};


int main(int argc, char** argv) {
    IntPtr x(12);
    //cout << x << endl;
    cout << x.getInt() << endl;
    cout << *x << endl;
    *x = 15;
    cout << *x << endl;
    
    //cant use new command
    //*x = new int(17);
    return 0;
}
