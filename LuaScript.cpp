#include "LuaScript.h"

LuaScript* LuaScript::create(const std::string& filename) {
   LuaScript* luaScript = new LuaScript();
   if(luaScript->init(filename))
	   return luaScript;

   //Failure case
   return NULL;
}

LuaScript::LuaScript()
{}

LuaScript::~LuaScript() {
	if(L) lua_close(L);
}

bool LuaScript::init(const std::string& filename)
{
	L = luaL_newstate();
    if (luaL_loadfile(L, filename.c_str()) || lua_pcall(L, 0, 0, 0)) {
        std::cout<<"Error: failed to load ("<<filename<<")"<<std::endl;
		L = 0;
		return false;
    }

    if(L) luaL_openlibs(L);
	return true;
}

void LuaScript::printError(const std::string& variableName, const std::string& reason) {
	std::cout<<"Error: can't get ["<<variableName<<"]. "<<reason<<std::endl;
}

/**
 * i = int
 * d = double
 * f = float
 * b = bool
 * s = char*
 **/
void LuaScript::lua_voidfunc(char* argdesc, ...)
{
	va_list arg_list;
	int numarg_list = strlen(argdesc);
	if(numarg_list < 1 || argdesc[0] != 's')
		return;

	va_start(arg_list, argdesc);

	char* funcname = va_arg(arg_list, char*);
	lua_getglobal(L, funcname);
 
	for(int i = 1; i < numarg_list; i++)
	{
		switch(argdesc[i])
		{
		case 'i':
			lua_pushnumber(L, va_arg(arg_list, int));
			break;
		case 'd':
			lua_pushnumber(L, va_arg(arg_list, double));
			break;
		case 'f':
			lua_pushnumber(L, va_arg(arg_list, float));
			break;
		case 'b':
			lua_pushboolean(L, va_arg(arg_list, bool));
			break;
		case 's':
			lua_pushstring(L, va_arg(arg_list, char*));
			break;
		}
	}
	va_end(arg_list);
 
	if(lua_pcall(L, numarg_list-1, 0, 0) != 0)
	   printf( "error running function `%s': %s", funcname, lua_tostring(L, -1));

  lua_pop(L,1);
}

/**
 * i = int
 * d = double
 * f = float
 * b = bool
 * s = char*
 **/
double LuaScript::lua_doublefunc(char* argdesc, ...)
{
	va_list arg_list;
	int numarg_list = strlen(argdesc);
	if(numarg_list < 1 || argdesc[0] != 's')
		return 0;

	va_start(arg_list, argdesc);

	char* funcname = va_arg(arg_list, char*);
	lua_getglobal(L, funcname);
 
	for(int i = 1; i < numarg_list; i++)
	{
		switch(argdesc[i])
		{
		case 'i':
			lua_pushnumber(L, va_arg(arg_list, int));
			break;
		case 'd':
			lua_pushnumber(L, va_arg(arg_list, double));
			break;
		case 'f':
			lua_pushnumber(L, va_arg(arg_list, float));
			break;
		case 'b':
			lua_pushboolean(L, va_arg(arg_list, bool));
			break;
		case 's':
			lua_pushstring(L, va_arg(arg_list, char*));
			break;
		}
	}
	va_end(arg_list);
 
	if(lua_pcall(L, numarg_list-1, 1, 0) != 0)
	{
	   printf( "error running function `%s': %s", funcname, lua_tostring(L, -1));
	   lua_pop(L, 1);
	   return 0;
	}

	if(!lua_isnumber(L, -1))
	{
		printf("function '%s' does not return a double", funcname);
		lua_pop(L, 1);
		return 0;
	}

	double result = lua_tonumber(L, -1);
	lua_pop(L,1);

	return result;
}

/**
 * i = int
 * d = double
 * f = float
 * b = bool
 * s = char*
 **/
int LuaScript::lua_intfunc(char* argdesc, ...)
{
	va_list arg_list;
	int numarg_list = strlen(argdesc);
	if(numarg_list < 1 || argdesc[0] != 's')
		return 0;

	va_start(arg_list, argdesc);

	char* funcname = va_arg(arg_list, char*);
	lua_getglobal(L, funcname);
 
	for(int i = 1; i < numarg_list; i++)
	{
		switch(argdesc[i])
		{
		case 'i':
			lua_pushnumber(L, va_arg(arg_list, int));
			break;
		case 'd':
			lua_pushnumber(L, va_arg(arg_list, double));
			break;
		case 'f':
			lua_pushnumber(L, va_arg(arg_list, float));
			break;
		case 'b':
			lua_pushboolean(L, va_arg(arg_list, bool));
			break;
		case 's':
			lua_pushstring(L, va_arg(arg_list, char*));
			break;
		}
	}
	va_end(arg_list);
 
	if(lua_pcall(L, numarg_list-1, 1, 0) != 0)
	{
	   printf( "error running function `%s': %s", funcname, lua_tostring(L, -1));
	   lua_pop(L, 1);
	   return 0;
	}

	if(!lua_isnumber(L, -1))
	{
		printf("function '%s' does not return a int", funcname);
		lua_pop(L, 1);
		return 0;
	}

	int result = (int)lua_tonumber(L, -1);
	lua_pop(L,1);

	return result;
}

/**
 * i = int
 * d = double
 * f = float
 * b = bool
 * s = char*
 **/
std::string LuaScript::lua_stringfunc(char* argdesc, ...)
{
	va_list arg_list;
	int numarg_list = strlen(argdesc);
	if(numarg_list < 1 || argdesc[0] != 's')
		return 0;

	va_start(arg_list, argdesc);

	char* funcname = va_arg(arg_list, char*);
	lua_getglobal(L, funcname);
 
	for(int i = 1; i < numarg_list; i++)
	{
		switch(argdesc[i])
		{
		case 'i':
			lua_pushnumber(L, va_arg(arg_list, int));
			break;
		case 'd':
			lua_pushnumber(L, va_arg(arg_list, double));
			break;
		case 'f':
			lua_pushnumber(L, va_arg(arg_list, float));
			break;
		case 'b':
			lua_pushboolean(L, va_arg(arg_list, bool));
			break;
		case 's':
			lua_pushstring(L, va_arg(arg_list, char*));
			break;
		}
	}
	va_end(arg_list);
 
	if(lua_pcall(L, numarg_list-1, 1, 0) != 0)
	{
	   printf( "error running function `%s': %s", funcname, lua_tostring(L, -1));
	   lua_pop(L, 1);
	   return 0;
	}

	if(!lua_isstring(L, -1))
	{
		printf("function '%s' does not return a double", funcname);
		lua_pop(L, 1);
		return 0;
	}

	std::string result = lua_tostring(L, -1);
	lua_pop(L,1);

	return result;
}

/**
 * i = int
 * d = double
 * f = float
 * b = bool
 * s = char*
 **/
bool LuaScript::lua_boolfunc(char* argdesc, ...)
{
	va_list arg_list;
	int numarg_list = strlen(argdesc);
	if(numarg_list < 1 || argdesc[0] != 's')
		return 0;

	va_start(arg_list, argdesc);

	char* funcname = va_arg(arg_list, char*);
	lua_getglobal(L, funcname);
 
	for(int i = 1; i < numarg_list; i++)
	{
		switch(argdesc[i])
		{
		case 'i':
			lua_pushnumber(L, va_arg(arg_list, int));
			break;
		case 'd':
			lua_pushnumber(L, va_arg(arg_list, double));
			break;
		case 'f':
			lua_pushnumber(L, va_arg(arg_list, float));
			break;
		case 'b':
			lua_pushboolean(L, va_arg(arg_list, bool));
			break;
		case 's':
			lua_pushstring(L, va_arg(arg_list, char*));
			break;
		}
	}
	va_end(arg_list);
 
	if(lua_pcall(L, numarg_list-1, 1, 0) != 0)
	{
	   printf( "error running function `%s': %s", funcname, lua_tostring(L, -1));
	   lua_pop(L, 1);
	   return 0;
	}

	if(!lua_isboolean(L, -1))
	{
		printf("function '%s' does not return a double", funcname);
		lua_pop(L, 1);
		return 0;
	}

	bool result = lua_toboolean(L, -1);
	lua_pop(L,1);

	return result;
}

std::vector<int> LuaScript::getIntVector(const std::string& name) {
    std::vector<int> v;
    lua_gettostack(name.c_str());
    if(lua_isnil(L, -1)) { // array is not found
        return std::vector<int>();
    }
    lua_pushnil(L);
    while(lua_next(L, -2)) { 
        v.push_back((int)lua_tonumber(L, -1));
        lua_pop(L, 1);
    }
    clean();
    return v;
}

std::vector<std::string> LuaScript::getTableKeys(const std::string& name) {
    std::string code = 
        "function getKeys(name) "
        "s = \"\""
        "for k, v in pairs(_G[name]) do "
        "    s = s..k..\",\" "
        "    end "
        "return s "
        "end"; // function for getting table keys
    luaL_loadstring(L, 
        code.c_str()); // execute code
    lua_pcall(L,0,0,0);
    lua_getglobal(L, "getKeys"); // get function
    lua_pushstring(L, name.c_str());
    lua_pcall(L, 1 , 1, 0); // execute function
    std::string test = lua_tostring(L, -1);
    std::vector<std::string> strings;
    std::string temp = "";
    std::cout<<"TEMP:"<<test<<std::endl;
    for(unsigned int i = 0; i < test.size(); i++) {     
        if(test.at(i) != ',') {
            temp += test.at(i);
        } else {
            strings.push_back(temp);
            temp= "";
        }
    }
    clean();
    return strings;
}