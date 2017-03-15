#include "Person.h"

Person::Person()
{
}

Person::Person(emSex sex):_sex(sex)
{
}

Person::~Person()
{
}

void Person::setSex(emSex sex)
{
	_sex = sex;
}

Person::emSex Person::getSex() const
{
	return _sex;
}