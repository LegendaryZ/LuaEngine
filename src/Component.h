#pragma once

class GameObject;

class Component
{
public:
	int gameObjectID;

	Component(void);
	~Component(void);

	virtual void addedToGameObject(GameObject* gameObject);
};

