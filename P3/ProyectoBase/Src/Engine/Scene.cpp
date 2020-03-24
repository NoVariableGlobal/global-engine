#include "Scene.h"
#include "ComponentsManager.h"
#include "Entity.h"
#include "Game.h"
#include "Loader.h"
#include "OgreVector3.h"
#include "PhysicsContext.h"

#include <iostream>
#include <json.h>

Scene::Scene(Game* _game) {
    componentManager = new ComponentsManager();

    PhysicsContext::getInstance()->init(0);

    Loader loader;
    loader.readPrefabs(this);

    game = _game;
}

Scene::~Scene() {
    clearEntities();
    clearPrefabs();

    delete componentManager;
    PhysicsContext::getInstance()->destroyWorld();
}

void Scene::changeScene(std::string _sceneName) {
    game->setChangeScene(true, _sceneName);
}

void Scene::load(std::string name) {
    Loader loader;
    loader.readObjects(name, this);
}

void Scene::update() {
    componentManager->update();
    componentManager->updateEvent();
    componentManager->updateSound();

    PhysicsContext::getInstance()->updateSimulation();
}

void Scene::render() { componentManager->render(); }

void Scene::handleInput(const SDL_Event& _event) {
    componentManager->handleInput(_event);
}

Entity* Scene::getEntitybyId(std::string id) {
    return entities.find(id)->second;
}

void Scene::addEntity(Entity* entity) {
    entities.emplace(entity->getId(), entity);
}

void Scene::clearEntities() {
    for (auto it : entities) {
        delete it.second;
    }

    entities.clear();
}

Entity* Scene::getInstanceOf(std::string _prefab, std::string _id) {
    Entity* instance = new Entity();

    instance->setId(_id);

    clonePrefabInfo(_prefab, instance);

    entities.emplace(instance->getId(), instance);

    return instance;
}

void Scene::clonePrefabInfo(std::string _prefab, Entity* _entity) {
    Loader loader;
    loader.setComponents(prefabs.find(_prefab)->second, _entity, this);
}

void Scene::addPrefab(std::string id, Json::Value components) {
    prefabs.emplace(id, components);
}

void Scene::clearPrefabs() {
    for (auto it : entities) {
        delete it.second;
    }

    prefabs.clear();
}

ComponentsManager* Scene::getComponentsManager() { return componentManager; }

void Scene::clearComponentsManager() { componentManager->clearComponents(); }
void Scene::deleteComponents() { componentManager->deleteComponents(); }
void Scene::insertComponents() { componentManager->insertComponents(); }
