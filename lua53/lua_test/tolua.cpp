#include "Student.h"
   
extern "C"  
{  
    #include "lua.h"  
    #include "lauxlib.h"  
    #include "lualib.h"  
}  

static int newPerson(lua_State *L);
static int l_setSex(lua_State *L);
static int l_getSex(lua_State *L);
static int l_person_gc(lua_State *L);

static const struct luaL_Reg personfunc[] = 
{
	{"new", newPerson},
	{NULL, NULL}
};

static const struct luaL_Reg personfunc_m [] = {
    {"setSex",l_setSex},
	{"getSex",l_getSex},
	{"__gc", l_person_gc},
    {NULL, NULL}
};


static int newStudent(lua_State *L);
static int l_setName(lua_State *L);
static int l_getName(lua_State *L);
static int l_gc(lua_State *L);

static const struct luaL_Reg studentfunc [] = {
	{"new", newStudent},
	{NULL, NULL}
};

static const struct luaL_Reg studentfunc_m [] = {
    {"setName",l_setName},
    //{"setAge", l_setAge},
    //{"print", l_print},
    {"getName",l_getName},
    //{"getAge", l_getAge},
	{"__gc", l_gc},
    {NULL, NULL}
};

static int luaopen_student(lua_State *L)
{
	luaL_newmetatable(L, "Student");
	lua_pushvalue(L, -1);
    lua_setfield(L, -2, "__index");
    luaL_setfuncs(L, studentfunc_m, 0);
    luaL_newlib(L, studentfunc);
	return 1;
}

int newStudent(lua_State *L)
{
	size_t studentSize = sizeof(Student*);
	Student **p = static_cast<Student**>(lua_newuserdata(L, studentSize));

	(*p) = new Student();

	luaL_getmetatable(L, "Student");
	lua_setmetatable(L, -2);
	return 1;
}

int l_setName(lua_State *L)
{
	Student **p = (Student**)luaL_checkudata(L,1,"Student");
    luaL_argcheck(L, p != NULL, 1, "invalid user data");
    
    luaL_checktype(L, -1, LUA_TSTRING);
    
    std::string name = lua_tostring(L, -1);
    (*p)->setName(name);

	return 1;
}

int l_getName(lua_State *L)
{
	Student **p = (Student**)luaL_checkudata(L,1,"Student");
    luaL_argcheck(L, p != NULL, 1, "invalid user data");

	lua_settop(L, 0);
    lua_pushstring(L, (*p)->getName().c_str());

	return 1;
}

int l_gc(lua_State *L)
{
	Student **p = (Student**)luaL_checkudata(L,1,"Student");
    luaL_argcheck(L, p != NULL, 1, "invalid user data");

	if (*p)
	{
		delete *p;
	}

	return 0;
}

int newPerson(lua_State *L)
{
	size_t size = sizeof(Person*);
	Person **p = static_cast<Person**>(lua_newuserdata(L, size));

	(*p) = new Person();

	luaL_getmetatable(L, "Person");
	lua_setmetatable(L, -2);
	return 1;
}

int l_setSex(lua_State *L)
{
	Person **p = (Person**)luaL_checkudata(L,1,"Person");
    luaL_argcheck(L, p != NULL, 1, "invalid user data");
    
    luaL_checktype(L, -1, LUA_TSTRING);
    
    int sex = lua_tonumber(L, -1);
    (*p)->setSex((Person::emSex)sex);

	return 1;
}

int l_getSex(lua_State *L)
{
	Person **p = (Person**)luaL_checkudata(L,1,"Person");
    luaL_argcheck(L, p != NULL, 1, "invalid user data");

	lua_settop(L, 0);
    lua_pushnumber(L, (int)((*p)->getSex()));

	return 1;
}

int l_person_gc(lua_State *L)
{	
	Person **p = (Person**)luaL_checkudata(L,1,"Person");
    luaL_argcheck(L, p != NULL, 1, "invalid user data");

	if (*p)
	{
		delete *p;
	}
	return 0;
}