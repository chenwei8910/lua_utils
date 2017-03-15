#pragma once

class Person
{
public:
	enum emSex
	{
		male	 = 0,
		female	 = 1,
	};

	Person();
	Person(emSex);
	~Person();

	void setSex(emSex);
	emSex getSex() const;

private:
	emSex _sex;
};