/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Node.h
 * Author: mtcummins
 *
 * Created on April 3, 2019, 2:55 PM
 */

#ifndef NODE_H
#define NODE_H

class Node{
private:
    int _data;
    Node* _next;
public:
    Node();
    Node(int d, Node* n);
    // no need for accessors and mutators because of friend designation
    friend class LinkedList;
};

#endif /* NODE_H */


