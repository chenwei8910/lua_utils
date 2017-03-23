// lua_test.cpp : �������̨Ӧ�ó������ڵ㡣
//

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

int main()
{
	// ����һ��state  
    lua_State *L = luaL_newstate(); 

	luaL_openlibs(L); 

	// ������ 
	//luaL_requiref(L, "person", luaopen_person, 1);
	//luaL_requiref(L, "student", luaopen_student, 1);

	// ���нű�
    if(luaL_dofile(L, "lua/student.lua"))
	{
		const char* error = luaL_checkstring(L, -1);
		printf("%s\n", error);
	}

	//luaL_dofile(L, "lua/main.lua"); 

       
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
   
    // �ر�state  
    lua_close(L);  

	// ��ͣ 
    printf( "Press enter to exit��" );  
    getchar();  
	return 0;
}

