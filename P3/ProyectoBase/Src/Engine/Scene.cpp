#include "Scene.h"
#include "Game.h"
#include "Entity.h"
#include "FactoriesFactory.h"

Scene::Scene() {}

Scene::~Scene() {}

void Scene::load(std::string name) {
  // Read entities and components from data file and create them

  // TODO: TEST - REMOVE BEFORE MERGING
  Entity* testEntity = new Entity();
  //testEntity->addComponent(FactoriesFactory::instance()->find("TestComponent")->create());
}

//Entity* Scene::getEntitybyId(Id id) {}