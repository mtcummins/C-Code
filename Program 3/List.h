/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   List.h
 * Author: mtcummins
 *
 * Created on April 15, 2019, 3:37 PM
 */

#ifndef LIST_H
#define LIST_H

class List{
private:
    ListRep* _rep;
public:
    list();
    List(const List& b);
    ~List();
    const List& operator=(const List& b);
    void Print();
    void Add(int a);
        
};

#endif /* LIST_H */
