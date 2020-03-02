#include "Scene.h"
#include "Game.h"
#include "Entity.h"
#include "FactoriesFactory.h"
#include "Loader.h"
#include "TransformComponent.h"

#include <iostream>

Scene::Scene() {}

Scene::~Scene() {}

void Scene::load(std::string name) {  
    Loader loader;
    loader.readEntities(name, entities);
    
    std::cout << dynamic_cast<TransformComponent*>(entities.find("PlayButton")->second->getComponent("TransformComponent"))->getPosition();
}

void Scene::update()
{
	while (!exit) {
		//UNDO COMMENT BEFORE MERGING
		/*componentManager.update();
		componentManager.handleInput();
		componentManager.render();
		componentManager.updateSound();
		componentManager.updateCamera();*/
	}
}

Entity* Scene::getEntitybyId(std::string id)
{
    return new Entity();
}