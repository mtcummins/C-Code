/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Node.cpp
 * Author: mtcummins
 * 
 * Created on April 3, 2019, 2:55 PM
 */

#include "Node.h"
Node::Node(): _data(0), _next(nullptr) {

}

Node::Node(int d, Node* n): _data(d), _next(n) {

}

