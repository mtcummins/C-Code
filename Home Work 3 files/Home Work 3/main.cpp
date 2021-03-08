/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: mtcummins
 *
 * Created on May 7, 2019, 1:38 PM
 */

#include <cstdlib>
#include <iostream>
#include <fstream>

using namespace std;
class IntMatrix{
private:
    int x[3][4]; 
public:
    IntMatrix(){
        for(int i=0;i<3;i++){
            for(int j=0;j<4;j++){
                x[i][j]=i+j;
            }
        }
    }
    
    int* operator[](int i){
        return x[i];
    }
    
    // const int* operator[](int i) const{
    //     return x[i];
    // }
    
    IntMatrix operator ()(int a,int b){
        cout << a << " " << b << endl;
        for(int i=0;i<3;i++){
            for(int j=0;j<4;j++){
                if(x[i][j]==a){
                    x[i][j]=b;
                }
            }
        }
    } 
    
    
    IntMatrix operator+(const IntMatrix b){
        IntMatrix temp;
        for(int i=0;i<3;i++){
            for(int j=0;j<4;j++){
                temp.x[i][j]=x[i][j]+b.x[i][j];
            }
        }
        return temp;
    }
    
    bool operator ==(const IntMatrix& b){
        bool same=true;
        for(int i=0;i<3;i++){
            for(int j=0;j<4;j++){
                if(x[i][j]!=b.x[i][j]){
                    same=false;
                }
            }
        }
        if(same==true){
            return 1;
        }else{
            return 0;
        }
    }
    
    void Print(){
         for(int i=0;i<3;i++){
            for(int j=0;j<4;j++){
                cout << x[i][j] << " ";
            }
            cout << endl;
        }
    }
};



class WordMatrix{
private:
    char* x[5];
    int _ctr;

public:
    WordMatrix(){
         for(int i=0;i<5;i++){
           char* t="a";
             x[i]=t;
             //cout << x[i] << " ";
         }
         //cout<< endl;
        
    }
    
    // WordMatrix operator =(string str){
    //     x.push_back(str);
    //     return WordMatrix;
    // }
    
    void AddWord(string s){
       
        
        //https://www.techiedelight.com/convert-string-char-array-cpp/
        // char* temp[s.size() + 1];
        // s.copy(temp, s.size() + 1);
        // temp[s.size()]='\0';
        
        //https://stackoverflow.com/questions/7352099/stdstring-to-char
        char* temp = &s[0u];
        
        
        int i=0;
        while(x[i]!="a"){
            i++;
            cout << i << " ";
        }
        cout<< endl;
        cout << "this is a test"<< endl;
        cout << i << endl;
        cout<< endl;
        cout<<x[0]<<endl;
        x[i]=temp;
        cout << x[0]<<endl;
       
    }
    
    void Print(){
        for(int i=0;i<5;i++){
            cout << x[i] << " ";
        }
        cout<< endl;
    }
    
};

/*
 * 
 */
int main(int argc, char** argv) {
   IntMatrix m, n;
    cout << "*** Printing if M == N" << endl;
    cout << (m == n) << endl;
    
        cout << "\n*** Printing M" << endl;
    m.Print();
       
    
    m[1][1] = 14;
        cout << "\n*** Printing M - changed to 14" << endl;
    m.Print();
        
    m(2,17);  // replace all 2's with a 17
        cout << "\n*** Printing M - changed 2 to 17" << endl;
    m.Print();
    
        cout << "\n*** Printing if M == N" << endl;
    cout << (m == n) << endl;
    
    IntMatrix p = m+n;
    cout << "\n*** Printing P" << endl;
    p.Print();

    {WordMatrix a;
     a.AddWord("hello");
     cout << "\n*** Printing A" << endl;
     a.Print();
    }
    
    WordMatrix a;
    a.AddWord("today");
    //
    a.Print();
    //
    a.AddWord("hello");
    
    cout << "\n*** Printing A" << endl;
    a.Print();
//  a = "world";
//  
//        cout << "\n*** Printing A" << endl;
//  a.Print();
//  WordMatrix b = a;
//  
//        cout << "\n*** Printing B" << endl;
//  b.Print();
//  
//        cout << "\n*** Adding Homework" << endl;
//  a.AddWord("homework");
//  a.Print();
//  b.Print();
//              out << "\n*** b[0] = a[3]" << endl;
//  b[0] = a[3];
//  a.Print();
//  b.Print();
//  WordMatrix c;
//  c = b = a;
//  
//        cout << "\n*** Printing A" << endl;
//  a.Print();
//  
//        cout << "\n*** Printing B" << endl;
//  b.Print();
//  
//        cout << "\n*** Printing C" << endl;
//  c.Print();
    
        return 0;
}

