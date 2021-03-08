/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   course.h
 * Author: mtcummins
 *
 * Created on March 29, 2019, 3:36 PM
 */


#ifndef COURSE_H
#define COURSE_H

#include <string>
using namespace std;

class Course{
    private:
	string _crsname;
	
    public:
	Course(){}   //inline method
	Course(string);
	void setName(string);
	string getName() const;
};
#endif /* COURSE_H */

