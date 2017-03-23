
#include "Person.h"

Person::Person():_name("default"), _age(0), _sex(emSex::male)
{
	cout<<"Person Contructor called"<<endl;
}

Person::Person(const string& name, int age, emSex sex):_name(name), _age(age), _sex(sex)
{
	cout<<"Person Contructor called"<<endl;
}

Person::~Person()
{
	cout<<"Person Destructor called"<<endl;
}

void Person::print()
{
    cout<<"My name is: "<<getName()<<", and my age is "<<getAge()<<endl;
}