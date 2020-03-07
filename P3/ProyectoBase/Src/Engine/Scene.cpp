#include "Scene.h"
#include "Game.h"
#include "Entity.h"
#include "FactoriesFactory.h"
#include "Loader.h"
#include "TransformComponent.h"
#include "ComponentsManager.h"
#include "CameraObject.h"

#include <iostream>

Scene::Scene() 
{
	componentManager = new ComponentsManager();
}

Scene::~Scene() 
{
	for (auto it : entities)
	{
		delete it.second;
	}
	delete componentManager;
}

void Scene::load(std::string name) 
{  
	Loader loader;
    loader.readObjects(name, entities, componentManager);
}

void Scene::update() 
{
	componentManager->update();
	componentManager->handleInput();
	componentManager->render();
	componentManager->updateSound();
}

Entity* Scene::getEntitybyId(std::string id)
{
    return entities.find(id)->second;
}

void Scene::clearComponentsManager()
{
	componentManager->clearComponents();
}
