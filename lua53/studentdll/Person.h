#pragma once

#include <iostream>
#include<string>
using namespace std;

class Person
{
public:
	enum emSex
	{
		male	 = 0,
		female	 = 1,
	};

	Person();
	Person(const string&, int, emSex);
	~Person();

	string getName() const {return _name;}
	void setName(const string& name) {_name = name;}
	int getAge() const {return _age;}
	void setAge(int age) {_age = age;}
	void setSex(emSex sex) {_sex = sex;}
	emSex getSex() const {return _sex;}

	virtual void print();

private:
	string _name;
	int _age;
	emSex _sex;
};