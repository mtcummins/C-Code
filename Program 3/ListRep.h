/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ListRep.h
 * Author: mtcummins
 *
 * Created on April 15, 2019, 3:37 PM
 */

#ifndef LISTREP_H
#define LISTREP_H

class ListRep{
private:
    Node* _head;
    Node* _tail;
    ListRep();
    ~ListRep();
    ListRep(const ListRep& b);
    
};
#endif /* LISTREP_H */
