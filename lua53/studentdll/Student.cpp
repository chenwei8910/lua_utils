
#include "Student.h"


Student::Student()
{
    cout<<"Student Contructor called"<<endl;
}

Student::Student(const string& name, int age, emSex sex, int grade):Person(name, age, sex), _grade(grade)
{
	cout<<"Student Contructor called"<<endl;
}

Student::~Student()
{
    cout<<"Student Destructor called"<<endl;
}

void Student::print()
{
    cout<<"I`m a student, my name is: "<<getName()<<", and my grade is "<<getGrade()<<endl;
}