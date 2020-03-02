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
  // Read entities and components from data file and create them

  // TODO: TEST - REMOVE BEFORE MERGING
    Loader loader;
    loader.readEntities(name, entities);

    std::cout << dynamic_cast<TransformComponent*>(entities.find("PlayButton")->second->getComponent("TransformComponent"))->getPosition();

    int a;
    a = 5;
}

Entity* Scene::getEntitybyId(std::string id)
{
    return new Entity();
}