#include "GameObject.h"
#include "Component.h"
#include "ScriptComponent.h"
#include <iostream>

GameObject::GameObject(int id)
{
	this->id = id;
}

GameObject::~GameObject(void)
{
	std::map<ComponentType, Component*>::iterator itr = components.begin();
	for(itr; itr != components.end();itr++)
		delete itr->second;
	components.clear();
}

void GameObject::update()
{
	printf("GameObject says hello!");
}

bool GameObject::addComponent(ComponentType type, Component* component, bool replaceExisting)
{
	std::map<ComponentType, Component*>::iterator itr = components.find(type);
	if(itr == components.end())
	{
		component->gameObjectID = id;
		components.insert(std::pair<ComponentType, Component*>(type, component));
		return true;
	}
	else if(replaceExisting)
	{
		delete itr->second;
		components.erase(itr);
		component->gameObjectID = id;
		components.insert(std::pair<ComponentType, Component*>(type, component));
		return true;
	}
	return false;
}

template <> 
inline ScriptComponent* GameObject::getComponent<ScriptComponent*>(ComponentType type) {
	std::map<ComponentType, Component*>::iterator itr = components.find(type);
	if(itr != components.end())
		return (ScriptComponent*)itr->second;
	else return 0;
}