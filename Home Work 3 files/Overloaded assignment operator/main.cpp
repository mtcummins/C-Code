/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: mtcummins
 *
 * Created on April 29, 2019, 3:11 PM
 */

#include <cstdlib>
#include <iostream>
#include <fstream>
using namespace std;

class Stuff{
private:
    int _things;
    string _string;
public:
    Stuff();
    Stuff(int x);
    int getThings()const;
    void setThings(int x);
    Stuff(string x);
    Stuff(char x);
    Stuff operator+(const int x);
    Stuff operator++();
    Stuff operator++(int);
    bool operator==(const Stuff& s)const;
};

Stuff::Stuff(){
    cout << "in the constructor" << endl;
    _things = 0;
}

Stuff::Stuff(int x){
    cout << "in the n-arg constructor" << endl;
    _things=x;
}

int Stuff::getThings() const{
    return _things;
}

void Stuff::setThings(int x){
    _things = x;
}

Stuff::Stuff(string x){
    _things = x.length();
    cout<<x.length();
}


Stuff::Stuff(char x){
    cout << "in char converter" << endl;
    _things = x;
}

Stuff Stuff::operator +(const int x){
    cout << "in operator +" << endl;
    Stuff t = *this;
    t._things = _things + x;
    return *this;
}
Stuff Stuff::operator ++(){
    cout << "in operator ++ prefix" << endl;
    _things = _things + 1;
    return *this;
}
Stuff Stuff::operator ++(int){
    Stuff t = *this;
    cout << "in operator ++ postfix" << endl;
    _things = _things + 1;
    return t;
}

bool Stuff::operator ==(const Stuff& s) const{
    cout << "in overloaded operator for ==" << endl;
    if(_things==s._things){
        cout << "in true" << endl;
        return true;
    }else {
        cout << "in false" << endl;
        return false;
    }
}



ostream& operator << (ostream& out, const Stuff& s){
    out << "in << operator" << endl;
    out << "the data in the stuff object is:" << endl;
    out << s.getThings() << endl;
    //works without this line.
    return out;
}


istream& operator >> (istream& in, Stuff& s){
    cout << "in operator <<" << endl;
    int x;
    in >> x;
    s.setThings(x);
}

/*
 * 
 */
int main(int argc, char** argv) {
//    cout << "in main - Stuff s" << endl;
//    Stuff s(1);
//    cout << "the _things in s is: " << s.getThings() << endl;
//    Stuff n(1);
//    n==s;
//    Stuff t(1);
//    n==t;
//    cout << s;
//    
    
    Stuff stuff(10);
    cout << stuff << endl;
    ofstream outfile("output.dat");
    outfile << stuff << endl;
    
    cout << (stuff++) << endl;
    cout << stuff << endl;
    
    Stuff stuff2;
    stuff2=2;
    cout << stuff2;
    //idk why this is broken but it is so its commented out.
    string string = "5";
    stuff2=string;
    cout << stuff2;
    stuff2 = '5';
    cout << stuff2 << endl;
    return 0;
}

