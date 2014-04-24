#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H


#include <map>

class Component;

class GameObject
{
public:
	enum ComponentType{
		LuaScript
	};

	GameObject(int id);
	~GameObject(void);

	bool update();

	bool addComponent(ComponentType type, Component* component, bool replaceExisting = false);

	template<typename T>
	T getComponent(ComponentType type)
	{
		return 0;
	}

	int getId()
	{
		return id;
	}

private:
	int id;
	std::map<ComponentType, Component*> components;
};

#endif /*GAMEOBJECT_H*/