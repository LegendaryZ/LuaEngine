#ifndef SCRIPTCOMPONENT_H
#define SCRIPTCOMPONENT_H

#include "Component.h"

class LuaScript;

class ScriptComponent : public Component
{
public:
	ScriptComponent(LuaScript* script);
	~ScriptComponent(void);

private:
	LuaScript* script;
};

#endif /*SCRIPTCOMPONENT_H*/