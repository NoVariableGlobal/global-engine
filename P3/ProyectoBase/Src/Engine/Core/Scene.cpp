#include "Scene.h"
#include "Game.h"
#include "Entity.h"
#include "../Factory/FactoriesFactory.h"
#include "../Managers/Loader.h"
#include "../Components/OtherComponents/TransformComponent.h"

#include <iostream>

Scene::Scene() {}

Scene::~Scene() {}

void Scene::load(std::string name) {  
    Loader loader;
    loader.readEntities(name, entities, componentManager);
    
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