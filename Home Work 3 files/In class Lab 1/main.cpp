/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: mtcummins
 *
 * Created on May 3, 2019, 2:55 PM
 */

#include <iostream>
using namespace std;

class Frac{
 public:
	Frac(int n=0, int d=3){
            _num=n; 
            _den=d; 
            cout << "in cons " << _num << " " << _den << endl;
        }
        
//	Frac operator+(Frac b) const{
//            cout << "in oper+" << endl;
//            return Frac(_num * b._den + _den * b._num, _den * b._den);
//	}
        
        operator double() const{
            double d = (_num/_den);
            return d;
        }
        
        
        int getNum(){
            return _num;
        }
        
        void setNum(int x){
            _num = x;
        }
        
        int getDen(){
            return _den;
        }
        
        void setDen(int x){
            _den = x;
        }
	
 private:
	int _num;
	int _den;
};



ostream& operator << (ostream& out, Frac& b){
    out << "in << operator" << endl;
    out << "the Fraction is " << b.getNum() << "/" << b.getDen() << endl; 
    return out;
}

Frac operator +(int x, Frac b){
    cout << "in operatpr +(int,Frac)" << endl;
    return Frac(b.getNum()*1+b.getDen()*x,b.getDen()*1);
    // could also not multiply by one a bunch but you know it still works
}

int main(){
	cout << "stmt 1: ";
	Frac f = 5;  
	cout << "stmt 2: ";
	Frac g = f + 2;
        cout << g << endl;
        Frac h = 2 + g;
	return 0;
}

