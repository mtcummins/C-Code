 /*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   LinkedList.cpp
 * Author: mtcummins
 * 
 * Created on April 3, 2019, 2:56 PM
 */

#include "LinkedList.h"

void LinkedList::Free(){
    
    
    //this is how the professor did it.
    Node* n = _head;
    while(n != nullptr){
        Node* t = n->_next;
        delete n;
        n = t;
    }
    
    
//    //this is my attempt its broken and dosnt work :(
//    if(_head!=nullptr){
//        return;
//    }
//    if (_head==_tail){
//        delete _head;
//        _head=_tail=nullptr;
//    }
}

void LinkedList::Copy(const LinkedList& b){
    //this is how the professor id this
    if(b._head == nullptr){
        _head=_tail=nullptr;
        return;
    }
    Node* t = new Node(b._head->_data, nullptr);
    _head = t;
    Node* p = _head;
    Node* n = b._head->_next;
    while(n != nullptr){
        t = new Node(n->_data, nullptr);
        p->_next = t;
        n = n->_next;
        p = p->_next;   
    }
    _tail = p;
}




void LinkedList::AddTail(int a){
    Node* n = new Node(a, nullptr);
    if (_head == nullptr){
        _head=_tail=n;
    }
    else{
        _tail->_next=n;
        _tail=n;
    }
}

void LinkedList::AddHead(int a){
    Node* n = new Node (a, _head);
    _head = n;
    if(_tail==nullptr){
        _tail=n;
    }
}

void LinkedList::Print(ostream& outfile){
    outfile << "Linked List" << endl;
    Node* n = _head;
    while(n!=nullptr){
        outfile << n->_data << endl;
        n = n->_next;
    }
    outfile << endl;
}

void LinkedList::RemoveTail(){
    if(_head==nullptr){
        return;
    }
    if (_head==_tail){
        delete _head;
        _head=_tail=nullptr;
    }
    else{
        Node* n = _head;
        while(n->_next != _tail){
          n = n->_next;  
        }
        delete _tail;
        _tail = n;
        n->_next = nullptr;
    }
 }

void LinkedList::RemoveHead(){
    if(_head==nullptr){
        return;
    }
    if (_head==_tail){
        delete _head;
        _head=_tail=nullptr;
    }
    else{
        //this is probably broken and needs fixing!
        Node* n = _head->_next;
        delete _head;
        _head = n;
    }
}

void LinkedList::Remove(int x){
    if(_head==nullptr){
        return;
    }
    if(_head==_tail){
        if(_head->_data == x){
            delete _head;
            _head = _tail = nullptr;
        }
    }
    else{
        Node* n = _head;
        Node* m = _head;
        while(n->_next != _tail){
        
            n = n->_next;
        }
    }
}



