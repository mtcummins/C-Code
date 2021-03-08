/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: mtcummins
 *
 * Created on May 29, 2019, 2:55 PM
 */

#include <cstdlib>
#include <string>
#include <string.h>
#include <iostream>
using namespace std;

template <class T>

class Test{
    private:
        T _val;
        static T _dval;
    public:
        Test(){ _val = _dval;}
        Test(T v): _val(v){}
        T getVal() const{return _val;}
        void setVal(T v);
        void print(){
            cout << "_val: " << _val << " " << &_val << endl;
            cout << "_dval: " << _dval << " " << &_dval << endl;
        }
};

template <class T>
T Test<T>::_dval;

template <class T>
void Test<T>::setVal(T v){
    _val = v;
}

int main(int argc, char** argv) {
    Test<int> t;
    t.setVal(5);
    t.print();
    Test<int> t2;
    t2.setVal(12);
    t2.print();
    Test<int> t3;
    t3.print();
    
    Test<string> s;
    s.setVal("hello");
    s.print();
    
    Test<int *> p;
    int* p2 = new int(5);
    p.setVal(p2);
    p.print();
    cout << &*p2<< " is the same as " << p2 << endl;
    return 0;
}

