#include "Scene.h"
#include "Game.h"
#include "Entity.h"
#include "Factory.h"

Scene::Scene() {}

Scene::~Scene() {}

void Scene::load(std::string name) {
  // Read entities and components from data file and create them

  // TODO: TEST - REMOVE BEFORE MERGING
  Entity* testEntity = new Entity();
  testEntity->addComponent(factory.find("TestComponent")->second->create());
}

//Entity* Scene::getEntitybyId(Id id) {}