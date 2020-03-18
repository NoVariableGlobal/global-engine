#include "Scene.h"
#include "Game.h"
#include "Entity.h"
#include "FactoriesFactory.h"
#include "Loader.h"
#include "TransformComponent.h"
#include "ComponentsManager.h"
#include "PhysicsContext.h"
#include "OgreVector3.h"

#include <json.h>
#include <iostream>


Scene::Scene(Game* _game) {
	componentManager = new ComponentsManager();
  
	PhysicsContext::getInstance()->init(0);

	Loader loader;
	loader.readPrefabs(this);

	game = _game;
}

Scene::~Scene() 
{
	clearEntities();
	clearPrefabs();

	delete componentManager;
	PhysicsContext::getInstance()->destroyWorld();
}

void Scene::changeScene(std::string _sceneName)
{
	game->setScene(_sceneName);
	sceneChange = true;
}

void Scene::load(std::string name) 
{  
	Loader loader;
    loader.readObjects(name, this);
}

void Scene::update() 
{
	componentManager->update();
	componentManager->updateEvent();
	componentManager->updateSound();

	PhysicsContext::getInstance()->updateSimulation();
}

void Scene::render()
{
	componentManager->render();
}

void Scene::handleInput(const SDL_Event& _event)
{
	componentManager->handleInput(_event);
}

Entity* Scene::getEntitybyId(std::string id)
{
    return entities.find(id)->second;
}

void Scene::addEntity(Entity* entity)
{
	entities.emplace(entity->getId(), entity);
}

void Scene::clearEntities()
{
	for (auto it : entities)
	{
		delete it.second;
	}

	entities.clear();
}

Entity* Scene::getInstanceOf(std::string id, int num)
{
	Entity* instance = new Entity();

	if (num != -1)
		instance->setId(id + std::to_string(num));
	else
		instance->setId(id);

	Loader loader;
	loader.setComponents(prefabs.find(id)->second, instance, this);

	entities.emplace(instance->getId(), instance);

	return instance;
}

void Scene::addPrefab(std::string id, Json::Value components)
{
	prefabs.emplace(id, components);
}

void Scene::clearPrefabs()
{
	for (auto it : entities)
	{
		delete it.second;
	}

	prefabs.clear();
}

ComponentsManager* Scene::getComponentsManager()
{
	return componentManager;
}

void Scene::clearComponentsManager()
{
	componentManager->clearComponents();
	entities.clear();
}
