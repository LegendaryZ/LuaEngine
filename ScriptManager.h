#ifndef SCRIPTMANAGER_H
#define SCRIPTMANAGER_H

#include <vector>
#include <string>
#include <map>
#include "LuaScript.h"

using namespace std;

/**
 * Script Manager is responsible for managing
 * all of the lua scripts. Tautology!
 **/
class ScriptManager
{
public:
	static ScriptManager* getInstance();
	~ScriptManager(void);

	bool loadScripts(const std::string& scriptDir);
	LuaScript* getScript(std::string& scriptName);
	bool unloadScript(std::string& scriptName);

	map<string, LuaScript*>& getScripts();
private:
	map<string, LuaScript*> scripts;

	ScriptManager(void);
	void getFilesInDir(const char* d, vector<string>& f);
};

#endif /*SCRIPTMANAGER_H*/

