// lua_test.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <iostream>  
#include <string.h>  
using namespace std; 

#include "tolua.cpp"

extern "C"  
{  
    #include "lua.h"  
    #include "lauxlib.h"  
    #include "lualib.h"  
} 

int _tmain(int argc, _TCHAR* argv[])
{
	//1.创建一个state  
    lua_State *L = luaL_newstate(); 

	luaL_openlibs(L);  

	/* 加载student类 */
	//luaL_requiref(L, "student", luaopen_student, 1);

	/* 运行脚本 */  
    //luaL_dofile(L, "lua/student.lua"); 

	luaL_dofile(L, "lua/main.lua"); 

       
    //2.入栈操作  
    //lua_pushstring(L, "I am so cool~");   
    //lua_pushnumber(L,20);  
   
    //3.取值操作  
    //if( lua_isstring(L,1)){             //判断是否可以转为string  
    //    cout<<lua_tostring(L,1)<<endl;  //转为string并返回  
    //}  
    //if( lua_isnumber(L,2)){  
    //    cout<<lua_tonumber(L,2)<<endl;  
    //}  
   
    //4.关闭state  
    lua_close(L);  

	/* 暂停 */  
    printf( "Press enter to exit…" );  
    getchar();  
	return 0;
}

