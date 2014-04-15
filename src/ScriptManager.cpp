#include "ScriptManager.h"

#include <vector>
#include <iostream>
#include <map>
#include <thread>
#include <tchar.h>
#include "Helper.h"
#include "LuaScript.h"

/**
 * Singleton Constructor/Accessor
 **/
ScriptManager* ScriptManager::getInstance()
{
	static ScriptManager* scriptManager;

	if(!scriptManager)
		scriptManager = new ScriptManager();

	return scriptManager;
}

ScriptManager::ScriptManager(void)
{
}


ScriptManager::~ScriptManager(void)
{
}

/**
 * Load all of the scripts from a directory into the 
 * map of scripts
 *
 * @param scriptDir		the directory of thes scripts
 *
 * @return success or failure
 **/
bool ScriptManager::loadScripts(const string& scriptDir)
{
	vector<string> scriptNames;
	getFilesInDir(scriptDir.c_str(), scriptNames);
	if(scriptNames.size() <= 0)
	{
		printf("Failed to find any .lua files");
		return false;
	}

	for(int i = 0; i < scriptNames.size(); i++)
	{
		//Load each script into the map
		LuaScript* script = LuaScript::create(scriptDir.substr(0, scriptDir.length()-1) + scriptNames[i]);
		if(script)
		{
			script->registercfunc(l_killScript, "kill");
			scripts.insert(pair<string, LuaScript*>(scriptNames[i].substr(0, scriptNames[i].length()-4), script));
		}
	}

	return true;
}

/**
 * Get the names of all the files in a directory
 *
 * @param d		The directory to search in
 * @param f		The vector to insert filenames into
 **/
void ScriptManager::getFilesInDir(const char* d, vector<string> & f)
{
    WIN32_FIND_DATA ffd;

	const int dirLen = strlen(d)+1;
	wchar_t* wtext = new wchar_t[dirLen];
	mbstowcs(wtext, d, strlen(d)+1);//Plus null
	LPWSTR dirName = wtext;

    HANDLE hFind = FindFirstFile(dirName, &ffd);
    if (hFind == INVALID_HANDLE_VALUE)
    {
        cerr << _T("Invalid handle value.") << GetLastError() << endl;
        return;
    }

    bool finished = false;
    while (!finished)
    {
		if(ffd.cFileName[0] != '.')
			f.push_back(wstrtostr(ffd.cFileName));

        if (!FindNextFile(hFind, &ffd))
            finished = true;
    }

	delete[] wtext;
}

/**
 * Run a script using an infinite loop
 * NOTE: NEVER CALL THIS FROM THE MAIN THREAD
 **/
void ScriptManager::runScript(LuaScript* script)
{
	script->lua_voidfunc("s", "init");
	while(script->getStatus() != LuaScript::Status::Dead)
		script->lua_voidfunc("s", "update");
}


/**
 * Get a particular script out of the map
 *
 * @param scriptName	The name of the script to search for
 *
 * @return LuaScript* or NULL if the script does not exist
 **/
LuaScript* ScriptManager::getScript(std::string& scriptName)
{
	map<string, LuaScript*>::iterator itr = scripts.find(scriptName);

	if(itr != scripts.end())
		return itr->second;
	else
		printf("Failed to find script '%s'", scriptName.c_str());

	return NULL;
}

/**
 * Delete a script from scripts
 *
 * @param scriptName	the name of the script to delete
 *
 * @return success or failure
 **/
bool ScriptManager::unloadScript(std::string& scriptName)
{
	map<string, LuaScript*>::iterator itr = scripts.find(scriptName);

	if(itr != scripts.end())
	{
		scripts.erase(scriptName);
		return true;
	}
	else
	{
		printf("Script '%s' cannot be erased as it does not exist", scriptName.c_str());
		return false;
	}
}

/**
 * Determine if a script exists
 *
 * @param scriptName	the name of the script to be searched for
 * @return  true or false
 **/
bool ScriptManager::hasScript(std::string& scriptName)
{
	map<string, LuaScript*>::iterator itr = scripts.find(scriptName);

	if(itr != scripts.end())
		return true;
	return false;
}

map<string, LuaScript*>& ScriptManager::getScripts()
{
	return scripts;
}