//
//  Student.cpp
//  MyCppGame
//
//  Created by guanghui on 8/11/14.
//
//

#include "Student.h"


Student::Student()
:name("default")
{
    cout<<"Student Contructor called"<<endl;
}

Student::~Student()
{
    cout<<"Student Destructor called"<<endl;
}

string Student::getName()
{
    return name;
}

void Student::setName(string name)
{
    this->name = name;
}

int Student::getAge()
{
    return age;
}

void Student::setAge(int age)
{
    this->age = age;
}

void Student::print()
{
    cout<<"My name is: "<<name<<", and my age is "<<age<<endl;
}