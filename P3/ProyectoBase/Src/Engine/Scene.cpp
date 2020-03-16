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


Scene::Scene() {
	componentManager = new ComponentsManager();
	PhysicsContext::getInstance()->init(0);
	PhysicsContext::getInstance()->createRB(Ogre::Vector3(10,10,10), Ogre::Vector3(10, 10, 10), 1);

	Loader loader;
	loader.readPrefabs(this);
}

Scene::~Scene() 
{
	clearEntities();
	clearPrefabs();

	delete componentManager;
	PhysicsContext::getInstance()->destroyWorld();
}

void Scene::load(std::string name) 
{  
	Loader loader;
    loader.readEntities(name, this);
}

void Scene::update() 
{
	componentManager->update();
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

	if (num != NULL)
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
}
