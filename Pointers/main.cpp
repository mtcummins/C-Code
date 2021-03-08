/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: mtcummins
 *
 * Created on May 13, 2019, 3:10 PM
 */

#include <cstdlib>
#include <string>
#include <iostream>
using namespace std;

class A{
private:
    string _name;
public:
    A(){_name="Caroline";}
    A(string s){_name=s;}
    virtual string getName(){return _name;}
    string getNameReverse(){
        string r= "";
        for (int i=_name.size(); i >=0; i--){
            r = r+_name[i];
        }
        return r;
    }
    string getNameReverse2(){
        string r= "";
        string::reverse_iterator ritr;
        for (ritr=_name.rbegin();ritr!=_name.rend(); ++ritr){
            r = r+*ritr;
        }
        return r;
    }
};

class B : public A{
private:
    int _id;
public:
    B(){_id=100;}
    int getID(){return _id;}
    
    //overloading the 
    string getName(){return A::getName() + " test";}
    
    //hiding getNameReverse method of base class
    string getNameRevers(int x){
        string tempName = A::getName();
        string r="";
        for (int i=x;i>=0;i--){
            r = r+tempName[i];
        }
        return r;
    }
    
};

int main(int argc, char** argv) {
    B* b = new B();
    cout << b->getID() << " " << b->getName() << endl;
    
    A* a = new A();
    cout << a->getName() << endl;

    // change A to B to get different results.
    A* a2 = new B();  
    //B* temp = (B*)a2;//static cast
    
    //dynamic cast
    B* temp2 = dynamic_cast<B*>(a2);
    if(temp2 == nullptr){
        // printing to a A object.
        cout << "A" << endl;
        cout << a2->getName()<<endl;
        cout << a2->getNameReverse2() << endl;
    }else{
        // printing to a B object.
        cout << "B" << endl;
        cout<< temp2->getID() << " " << temp2->getName() << endl;
        cout<<temp2->getNameRevers(3)<< endl;
    }

     
    return 0;
}

