/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   LinkedList.h
 * Author: mtcummins
 *
 * Created on April 3, 2019, 2:56 PM
 */

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
using namespace std;
#include "Node.h"

class LinkedList{
private:
    Node* _head;
    Node* _tail;
    void Remove(Node* n);
    void Free();
    void Copy(const LinkedList& b);

public:
    LinkedList(){
	_head = _tail = nullptr;
    }

    // Copy Constructor
    LinkedList(const LinkedList& b){
        Copy(b);
    }

    // Destructor
    ~LinkedList(){
        Free();
    }

    // overloaded assignment operator
    const LinkedList& operator=(const LinkedList& b){
        if (this != &b){
            Free();
            Copy(b);
        }
        return *this;
    }

    // pre: none
    // post: parameter added to end of list
    void AddTail(int a);

    // pre: none
    // post: parameter added to front of list
    void AddHead(int a);

    // pre: list is not empty
    // post: element at end of list removed
    void RemoveTail();

    // pre: list is not empty
    // post: element at front of list removed
    void RemoveHead();

    // pre: list is not empty
    // post: elements containing parameter removed from list
    void Remove(int x);

    // pre: list is not empty
    // post: true returned if parameter found in list, else false returned
    bool SearchFound(int x);

    // pre: list is not empty
    // post: number of times element found in list is returned
    int SearchCount(int x);

    // This method is used for testing only.
    // pre: parameter references valid output stream
    // post: contents of list printed to parameter stream
    void Print(ostream &outfile);
};

#endif /* LINKEDLIST_H */

