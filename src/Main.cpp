#include "LuaScript.h"
#include "ScriptManager.h"
#include "ThreadManager.h"
#include "Helper.h"
#include <iostream>
#include <string>
#include <stdarg.h>

using namespace std;

/**
 * Test the player script
 **/
void testPlayerScript()
{
	printf("=====================================================\n");
	printf("              Test player Script                     \n");
	printf("=====================================================\n\n");

	LuaScript* luaScript = ScriptManager::getInstance()->getScript(string("player"));
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
		std::vector<int> v = luaScript->getVector<int>("array");
		std::cout<<"Contents of array:";
		for(std::vector<int>::iterator it = v.begin();
			it != v.end();
			it++) {
			std::cout<<*it<<",";
		}
		std::cout<<std::endl;

		// getting arrays
		std::vector<std::string> v2 = luaScript->getVector<std::string>("inv");
		std::cout<<"Contents of inv:";
		for(std::vector<std::string>::iterator it = v2.begin();
			it != v2.end();
			it++) {
			std::cout<<*it<<",";
		}
		std::cout<<std::endl;

		// getting arrays
		std::vector<bool> v3 = luaScript->getVector<bool>("boolArray");
		std::cout<<"Contents of boolArray:";
		for(std::vector<bool>::iterator it = v3.begin();
			it != v3.end();
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
}

int main()
{
	ScriptManager::getInstance()->loadScripts("src\\Scripts\\*");

	testPlayerScript();
	
	/*
	map<string, LuaScript*>::iterator scriptItr = ScriptManager::getInstance()->getScripts().begin();
	
	//Run all scripts
	for(scriptItr; scriptItr != ScriptManager::getInstance()->getScripts().end(); scriptItr++)
		scriptItr->second->infiniteRun();
	*/
	
	printf("\n\n");
	system("PAUSE");
	return 0;
}