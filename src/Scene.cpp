#include "Scene.h"
#include "GameObject.h"

Scene::Scene(void)
{
	gameObjects.clear();
}


Scene::~Scene(void)
{
}

bool Scene::addGameObject(GameObject object, bool replaceExisting)
{
	std::map<int, GameObject>::iterator itr = gameObjects.find(object.getId());
	if(itr == gameObjects.end())
	{
		int id = object.getId();
		gameObjects.insert(std::pair<int, GameObject>(id, object));
		return true;
	}
	else if(replaceExisting)
	{
		gameObjects.erase(itr);
		int id = object.getId();
		gameObjects.insert(std::pair<int, GameObject>(id, object));
		return true;
	}
	return false;
}

void Scene::update()
{

}
