//
//  Student.h
//  MyCppGame
//
//  Created by guanghui on 8/11/14.
//
//

#ifndef __MyCppGame__Student__
#define __MyCppGame__Student__

#include <iostream>
#include<string>
using namespace std;

class Student
{
public:
    Student();
    ~Student();
    string getName();
    void setName(string name);
    int getAge();
    void setAge(int age);
    void print();
    
private:
    string name;
    int age;
};

#endif /* defined(__MyCppGame__Student__) */