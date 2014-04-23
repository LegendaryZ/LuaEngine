#ifndef SCENE_H
#define SCENE_H

#include <map>

class GameObject;

class Scene
{
public:
	Scene(void);
	~Scene(void);

	void update();

	bool addGameObject(GameObject object, bool replaceExistsing = false);

private:
	std::map<int, GameObject> gameObjects;
};

#endif /*SCENE_H*/