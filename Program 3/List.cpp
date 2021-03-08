/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   List.cpp
 * Author: mtcummins
 * 
 * Created on April 15, 2019, 3:37 PM
 */

#include "List.h"
#include "ListRep.h"

List::List(){
    _rep = new ListRep();
}