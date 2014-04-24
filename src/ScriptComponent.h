#ifndef SCRIPTCOMPONENT_H
#define SCRIPTCOMPONENT_H

#include "Component.h"

class LuaScript;

class ScriptComponent : public Component
{
public:
	ScriptComponent(LuaScript* script);
	~ScriptComponent(void);

	virtual void addedToGameObject(GameObject* gameObject);
private:
	LuaScript* script;
};

#endif /*SCRIPTCOMPONENT_H*/