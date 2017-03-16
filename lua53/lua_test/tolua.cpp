#include "Student.h"
   
extern "C"  
{  
    #include "lua.h"  
    #include "lauxlib.h"  
    #include "lualib.h"  
}  

static int newPerson(lua_State *L);
static int l_setName(lua_State *L);
static int l_getName(lua_State *L);
static int l_setAge(lua_State *L);
static int l_getAge(lua_State *L);
static int l_setSex(lua_State *L);
static int l_getSex(lua_State *L);
static int l_print(lua_State *L);
static int l_gc_person(lua_State *L);

static const struct luaL_Reg personfunc_m [] = {
	{"new", newPerson},
	{"setName",l_setName},
	{"getName",l_getName},
	{"setAge",l_setAge},
	{"getAge",l_getAge},
    {"setSex",l_setSex},
	{"getSex",l_getSex},
	{"print", l_print},
    {NULL, NULL}
};

static int luaopen_person(lua_State *L)
{
	// 对象的元表
	luaL_newmetatable(L, "Person");
	int meta = lua_gettop(L);

	// 设置对象元表的gc方法
	lua_pushcfunction(L, l_gc_person);
	lua_setfield(L, meta, "__gc");

	// 类原型
	luaL_newlib(L, personfunc_m);
	//int proto = lua_gettop(L);

	// 在全局表中记录类原型
	lua_pushstring(L, "Person");
	lua_pushvalue(L, -2);
	lua_settable(L, LUA_RIDX_GLOBALS);

	// 设置对象元表的__index为类原型
	lua_pushvalue(L, -1);
    lua_setfield(L, meta, "__index");
    
	return 1;
}

static int newStudent(lua_State *L);
static int l_setGrade(lua_State *L);
static int l_getGrade(lua_State *L);

static int l_gc_student(lua_State *L);

static const struct luaL_Reg studentfunc_m [] = {
	{"new", newStudent},
    {"setGrade",l_setGrade},
	{"getGrade",l_getGrade},
    {NULL, NULL}
};

static int luaopen_student(lua_State *L)
{
	// 对象的元表
	luaL_newmetatable(L, "Student");
	int meta = lua_gettop(L);

	// 设置对象元表的gc方法
	lua_pushcfunction(L, l_gc_student);
	lua_setfield(L, meta, "__gc");

	// 类原型
	luaL_newlib(L, studentfunc_m);
	//int proto = lua_gettop(L);

	// 在全局表中记录类原型
	lua_pushstring(L, "Student");
	lua_pushvalue(L, -2);
	lua_settable(L, LUA_RIDX_GLOBALS);

	// 设置student原型的元表为person对象的元表
	luaL_getmetatable(L, "Person");
	lua_setmetatable(L, -2);

	// 设置student对象元表的__index为student类原型
	lua_pushvalue(L, -1);
    lua_setfield(L, meta, "__index");

	return 1;
}

int newPerson(lua_State *L)
{
	// 参数数量
	int argsNum = lua_gettop(L);

	// 创建一个Person类大小的userdata
	size_t personSize = sizeof(Person);
	void *pBuff = lua_newuserdata(L, personSize);
	
	Person* p = 0;
	if(argsNum > 0)
	{
		std::string name = luaL_checkstring (L, 1);
		int age = static_cast<int>(luaL_checkinteger(L, 2));
		Person::emSex sex = static_cast<Person::emSex>(luaL_checkinteger (L, 3));
		//(*p) = new Person(name, age, sex);

		// 利用placement new在已分配的userdata的内存中初始化person对象
		p = new(pBuff) Person(name, age, sex); 
	}
	else
	{
		// 利用placement new在已分配的userdata的内存中初始化person对象
		p = new(pBuff) Person();
	}

	// 设置userdata的元表为Person
	luaL_getmetatable(L, "Person");
	lua_setmetatable(L, -2);
	return 1;
}

int l_gc_person(lua_State *L)
{	
	Person *p = static_cast<Person*>(luaL_checkudata(L,1,"Person"));
    luaL_argcheck(L, p != NULL, 1, "invalid user data");

	if (p)
	{
		// 只调用析构函数不释放内存，因为usedata的内存由lua分配也由它释放
		p->~Person();
	}
	return 0;
}

int newStudent(lua_State *L)
{
	int argsNum = lua_gettop(L);

	size_t studentSize = sizeof(Student);
	void *pBuff = lua_newuserdata(L, studentSize);

	if(argsNum > 0)
	{
		std::string name = luaL_checkstring (L, 1);
		int age = static_cast<int>(luaL_checkinteger(L, 2));
		Person::emSex sex = static_cast<Person::emSex>(luaL_checkinteger (L, 3));
		int grade = static_cast<int>(luaL_checkinteger(L, 4));
		new(pBuff) Student(name, age, sex, grade);
	}
	else
	{
		new(pBuff) Student();
	}

	luaL_getmetatable(L, "Student");
	lua_setmetatable(L, -2);
	return 1;
}

int l_gc_student(lua_State *L)
{
	Student *p = static_cast<Student*>(luaL_checkudata(L,1,"Student"));
    luaL_argcheck(L, p != NULL, 1, "invalid user data");

	if (p)
	{
		p->~Student();
	}

	return 0;
}

int l_setName(lua_State *L)
{
	//Person **p = (Person**)luaL_checkudata(L,1,"Person");
	Person *p = static_cast<Person*>(lua_touserdata(L,1));
    luaL_argcheck(L, p != NULL, 1, "invalid user data");
    
    luaL_checktype(L, -1, LUA_TSTRING);
    
    std::string name = lua_tostring(L, -1);
    p->setName(name);

	return 1;
}

int l_getName(lua_State *L)
{
	Person *p = static_cast<Person*>(lua_touserdata(L,1));
    luaL_argcheck(L, p != NULL, 1, "invalid user data");

	lua_settop(L, 0);
    lua_pushstring(L, p->getName().c_str());

	return 1;
}

int l_setAge(lua_State *L)
{
	//Person **p = (Person**)luaL_checkudata(L,1,"Person");
	Person *p = static_cast<Person*>(lua_touserdata(L,1));
    luaL_argcheck(L, p != NULL, 1, "invalid user data");
    
    int age = static_cast<int>(luaL_checkinteger(L, -1));
    p->setAge(age);

	return 1;
}

int l_getAge(lua_State *L)
{
	Person *p = static_cast<Person*>(lua_touserdata(L,1));
    luaL_argcheck(L, p != NULL, 1, "invalid user data");

	lua_settop(L, 0);
    lua_pushinteger(L, p->getAge());

	return 1;
}

int l_setSex(lua_State *L)
{
	Person *p = static_cast<Person*>(lua_touserdata(L,1));
    luaL_argcheck(L, p != NULL, 1, "invalid user data");
    
    Person::emSex sex = static_cast<Person::emSex>(luaL_checkinteger(L, -1));
    p->setSex(sex);

	return 1;
}

int l_getSex(lua_State *L)
{
	//Person *p = (Person*)luaL_checkudata(L,1,"Person");
	Person *p = static_cast<Person*>(lua_touserdata(L,1));
    luaL_argcheck(L, p != NULL, 1, "invalid user data");

	lua_settop(L, 0);
    lua_pushinteger(L, (int)(p->getSex()));

	return 1;
}

int l_setGrade(lua_State *L)
{
	Student *p = static_cast<Student*>(lua_touserdata(L,1));
    luaL_argcheck(L, p != NULL, 1, "invalid user data");
    
    int grade = static_cast<int>(luaL_checkinteger(L, -1));
    p->setGrade(grade);

	return 1;
}

int l_getGrade(lua_State *L)
{
	Student *p = static_cast<Student*>(lua_touserdata(L,1));
    luaL_argcheck(L, p != NULL, 1, "invalid user data");

	lua_settop(L, 0);
    lua_pushinteger(L, p->getGrade());

	return 1;
}

// print函数是在Person中定义的虚函数，Student中重写了该函数，
// 对于虚函数我们只需要注册在父类的原型中即可，由父类指针可以调用到正确的版本
int l_print(lua_State *L)
{
	// 将userdata的内存地址转化为父类对象指针
	// 此处没有用lua_checkudata校验userdata的元表名是否是Person是因为userdata对象实例也可能是Student或者其它的派生类（如果有的话）
	Person *p = static_cast<Person*>(lua_touserdata(L,1));
    luaL_argcheck(L, p != NULL, 1, "invalid user data");

	p->print();

	return 1;
}
