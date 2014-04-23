#include "ScriptComponent.h"


ScriptComponent::ScriptComponent(LuaScript* script) : Component()
{
	this->script = script;
}


ScriptComponent::~ScriptComponent(void)
{
}
