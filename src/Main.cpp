#include "LuaScript.h"
#include "ScriptManager.h"
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
	printf("\n===============================================================\n");
	printf("Test LuaScript\n");
	printf("===============================================================\n\n");

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
}

int main()
{
	ScriptManager::getInstance()->loadScripts("src\\Scripts\\*");
	
	map<string, LuaScript*>::iterator scriptItr = ScriptManager::getInstance()->getScripts().begin();

	//Init all scripts
	for(scriptItr; scriptItr != ScriptManager::getInstance()->getScripts().end(); scriptItr++)
		scriptItr->second->lua_voidfunc("s", "init");

	bool quit = false;
	int count = 0;
	while(!quit)
	{
		printf("\n %d \n", ++count);
		if(ScriptManager::getInstance()->getScript(std::string("player")))
		{
			ScriptManager::getInstance()->getScript(std::string("player"))->lua_voidfunc("s", "update");
			if(ScriptManager::getInstance()->getScript(std::string("player"))->getStatus()  == LuaScript::Status::Dead)
				ScriptManager::getInstance()->unloadScript(std::string("player"));
		}

		if(ScriptManager::getInstance()->getScript(std::string("luascript")))
		{
			ScriptManager::getInstance()->getScript(std::string("luascript"))->lua_voidfunc("s", "update");
			if(ScriptManager::getInstance()->getScript(std::string("luascript"))->getStatus()  == LuaScript::Status::Dead)
				ScriptManager::getInstance()->unloadScript(std::string("luascript"));
		}

		if(ScriptManager::getInstance()->getScripts().size() == 0)
			quit = true;
	}
	/*
	testPlayerScript();

	printf("\n\nDeleting 'player'...\n");
	ScriptManager::getInstance()->unloadScript(string("player"));
	testPlayerScript();
	*/
	printf("\n\n");
	system("PAUSE");
	return 0;
}