#pragma once

#include "Person.h"

class Student: public Person
{
public:
    Student();
	Student(const string&, int, emSex, int);
    ~Student();
	int getGrade() const {return _grade;}
	void setGrade(int grade) { _grade = grade;}
    void print();
    
private:
    int _grade;
};