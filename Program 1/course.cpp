/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "course.h"

Course::Course(string n)
	: _crsname(n)
	{}
	
void Course::setName(string s){
	_crsname = s;
}

string Course::getName() const{
	return _crsname;
}

