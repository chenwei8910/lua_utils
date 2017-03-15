// lua_test.cpp : �������̨Ӧ�ó������ڵ㡣
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
	//1.����һ��state  
    lua_State *L = luaL_newstate(); 

	luaL_openlibs(L);  

	/* ����student�� */
	//luaL_requiref(L, "student", luaopen_student, 1);

	/* ���нű� */  
    //luaL_dofile(L, "lua/student.lua"); 

	luaL_dofile(L, "lua/main.lua"); 

       
    //2.��ջ����  
    //lua_pushstring(L, "I am so cool~");   
    //lua_pushnumber(L,20);  
   
    //3.ȡֵ����  
    //if( lua_isstring(L,1)){             //�ж��Ƿ����תΪstring  
    //    cout<<lua_tostring(L,1)<<endl;  //תΪstring������  
    //}  
    //if( lua_isnumber(L,2)){  
    //    cout<<lua_tonumber(L,2)<<endl;  
    //}  
   
    //4.�ر�state  
    lua_close(L);  

	/* ��ͣ */  
    printf( "Press enter to exit��" );  
    getchar();  
	return 0;
}

