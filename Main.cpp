#include "LuaScript.h"
#include <iostream>
#include <string>
#include <stdarg.h>
using namespace std;

extern "C" {
  static int l_cppfunction(lua_State *L) {
    double arg = luaL_checknumber(L,1);
    lua_pushnumber(L, arg * 0.5);
    return 1;
  }
}


int main()
{
	printf("===============================================================\n");
  cout << "** Test Lua embedding" << endl;
  printf("===============================================================\n\n");
  cout << "** Init Lua" << endl;
  lua_State *L;
  L = luaL_newstate();
  cout << "** Load the (optional) standard libraries, to have the print function" << endl;
  luaL_openlibs(L);
  cout << "** Load chunk. without executing it" << endl;
  if (luaL_loadfile(L, "luascript.lua")) {
    cerr << "Something went wrong loading the chunk (syntax error?)" << endl;
    cerr << lua_tostring(L, -1) << endl;
    lua_pop(L,1);
  }

  cout << "** Make a insert a global var into Lua from C++" << endl;
  lua_pushnumber(L, 1.1);
  lua_setglobal(L, "cppvar");

  cout << "** Execute the Lua chunk" << endl;
  if (lua_pcall(L,0, LUA_MULTRET, 0)) {
    cerr << "Something went wrong during execution" << endl;
    cerr << lua_tostring(L, -1) << endl;
    lua_pop(L,1);
  }

  cout << "** Read a global var from Lua into C++" << endl;
  lua_getglobal(L, "luavar");
  double luavar = lua_tonumber(L,-1);
  lua_pop(L,1);
  cout << "C++ can read the value set from Lua luavar = " << luavar << endl;

  cout << "** Execute a Lua function from C++" << endl;
  lua_getglobal(L, "myluafunction");
  lua_pushnumber(L, 5);
  lua_pcall(L, 1, 1, 0);
  cout << "The return value of the function was " << lua_tostring(L, -1) << endl;
  lua_pop(L,1);

  cout << "** Execute a C++ function from Lua" << endl;
  cout << "**** First register the function in Lua" << endl;
  lua_pushcfunction(L,l_cppfunction);
  lua_setglobal(L, "cppfunction");

  cout << "**** Call a Lua function that uses the C++ function" << endl;
  lua_getglobal(L, "myfunction");
  lua_pushnumber(L, 5);
  lua_pcall(L, 1, 1, 0);
  cout << "The return value of the function was " << lua_tonumber(L, -1) << endl;
  lua_pop(L,1);

  cout << "** Release the Lua enviroment" << endl;
  lua_close(L);
  
  printf("\n===============================================================\n");
  printf("Test LuaScript\n");
  printf("===============================================================\n\n");

  LuaScript* luaScript = LuaScript::create("player.lua");
  if(luaScript)
  {
	float posX = luaScript->get<float>("player.position.x");
    float posY = luaScript->get<float>("player.position.y");
    std::string filename = luaScript->get<std::string>("player.filename");
    int hp = luaScript->get<int>("player.HP");

    std::cout<<"Position X = "<<posX<<", Y = "<<posY<<std::endl;
    std::cout<<"Filename:"<<filename<<std::endl;
    std::cout<<"HP:"<<hp<<std::endl;

    // getting arrays
    std::vector<int> v = luaScript->getIntVector("array");
    std::cout<<"Contents of array:";
    for(std::vector<int>::iterator it = v.begin();
            it != v.end();
            it++) {
            std::cout<<*it<<",";
    }
    std::cout<<std::endl;

    // getting table keys:
    std::vector<std::string> keys = luaScript->getTableKeys("player");
    std::cout<<"Keys of [player] table:";
    for(std::vector<std::string>::iterator it = keys.begin();
            it != keys.end();
            it++) {
            std::cout<<*it<<",";
    }

	printf("\n\nCalling Lua Functions from C++:\n");
	luaScript->lua_voidfunc("ss", "printHelloWorld", "Hello World!");

	std::string testString = luaScript->lua_stringfunc("si", "myluafunction", 5);
	std::cout << testString << std::endl;
  }

  printf("\n\n");
  system("PAUSE");
  return 0;
}