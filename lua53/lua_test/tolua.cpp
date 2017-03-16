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
	// �����Ԫ��
	luaL_newmetatable(L, "Person");
	int meta = lua_gettop(L);

	// ���ö���Ԫ���gc����
	lua_pushcfunction(L, l_gc_person);
	lua_setfield(L, meta, "__gc");

	// ��ԭ��
	luaL_newlib(L, personfunc_m);
	//int proto = lua_gettop(L);

	// ��ȫ�ֱ��м�¼��ԭ��
	lua_pushstring(L, "Person");
	lua_pushvalue(L, -2);
	lua_settable(L, LUA_RIDX_GLOBALS);

	// ���ö���Ԫ���__indexΪ��ԭ��
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
	// �����Ԫ��
	luaL_newmetatable(L, "Student");
	int meta = lua_gettop(L);

	// ���ö���Ԫ���gc����
	lua_pushcfunction(L, l_gc_student);
	lua_setfield(L, meta, "__gc");

	// ��ԭ��
	luaL_newlib(L, studentfunc_m);
	//int proto = lua_gettop(L);

	// ��ȫ�ֱ��м�¼��ԭ��
	lua_pushstring(L, "Student");
	lua_pushvalue(L, -2);
	lua_settable(L, LUA_RIDX_GLOBALS);

	// ����studentԭ�͵�Ԫ��Ϊperson�����Ԫ��
	luaL_getmetatable(L, "Person");
	lua_setmetatable(L, -2);

	// ����student����Ԫ���__indexΪstudent��ԭ��
	lua_pushvalue(L, -1);
    lua_setfield(L, meta, "__index");

	return 1;
}

int newPerson(lua_State *L)
{
	// ��������
	int argsNum = lua_gettop(L);

	// ����һ��Person���С��userdata
	size_t personSize = sizeof(Person);
	void *pBuff = lua_newuserdata(L, personSize);
	
	Person* p = 0;
	if(argsNum > 0)
	{
		std::string name = luaL_checkstring (L, 1);
		int age = static_cast<int>(luaL_checkinteger(L, 2));
		Person::emSex sex = static_cast<Person::emSex>(luaL_checkinteger (L, 3));
		//(*p) = new Person(name, age, sex);

		// ����placement new���ѷ����userdata���ڴ��г�ʼ��person����
		p = new(pBuff) Person(name, age, sex); 
	}
	else
	{
		// ����placement new���ѷ����userdata���ڴ��г�ʼ��person����
		p = new(pBuff) Person();
	}

	// ����userdata��Ԫ��ΪPerson
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
		// ֻ���������������ͷ��ڴ棬��Ϊusedata���ڴ���lua����Ҳ�����ͷ�
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

// print��������Person�ж�����麯����Student����д�˸ú�����
// �����麯������ֻ��Ҫע���ڸ����ԭ���м��ɣ��ɸ���ָ����Ե��õ���ȷ�İ汾
int l_print(lua_State *L)
{
	// ��userdata���ڴ��ַת��Ϊ�������ָ��
	// �˴�û����lua_checkudataУ��userdata��Ԫ�����Ƿ���Person����Ϊuserdata����ʵ��Ҳ������Student���������������ࣨ����еĻ���
	Person *p = static_cast<Person*>(lua_touserdata(L,1));
    luaL_argcheck(L, p != NULL, 1, "invalid user data");

	p->print();

	return 1;
}
