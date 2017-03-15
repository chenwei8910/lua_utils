#include "Student.h"
   
extern "C"  
{  
    #include "lua.h"  
    #include "lauxlib.h"  
    #include "lualib.h"  
}  

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