#include "Scene.h"
#include "Component.h"
#include "ComponentsManager.h"
#include "Entity.h"
#include "Game.h"
#include "Loader.h"
#include "OgreVector3.h"
#include "PhysicsContext.h"
#include "Util.h"

#include <OgreFrameListener.h>
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
    return assert_find(entities, id);
}

std::vector<Entity*> Scene::getEntitiesbyTag(std::string tag) {
    std::vector<Entity*> tagEntities;

    for (auto it : entities) {
        if (it.second->getTag() == tag) {
            tagEntities.push_back(it.second);
        }
    }
    return tagEntities;
}

void Scene::addEntity(Entity* entity) {
    entities.emplace(entity->getId(), entity);
}

std::map<std::string, Entity*>::iterator Scene::deleteEntity(Entity* entity) {
    std::map<std::string, Component*>& components = entity->getAllComponents();
    for (auto it : components) {
        it.second->destroy();
    }
    std::string id = entity->getId();
    delete entities.find(id)->second;
    return entities.erase(entities.find(id));
}

void Scene::clearEntities() {
    for (auto it : entities) {
        delete it.second;
    }

    entities.clear();
}

void Scene::clearNonPersistantEntities() {
    auto it = entities.begin();
    while (it != entities.end()) {
        if (!it->second->isPersistent())
            it = deleteEntity(it->second);
        else
            ++it;
    }
}

Entity* Scene::getInstanceOf(std::string _prefab, std::string _id,
                             std::string _tag) {
    Entity* instance = new Entity();

    instance->setId(_id);
    instance->setTag(_tag);

    clonePrefabInfo(_prefab, instance);

    entities.emplace(instance->getId(), instance);

    return instance;
}

void Scene::clonePrefabInfo(std::string _prefab, Entity* _entity) {
    Loader loader;
    Json::Value value = assert_find(prefabs, _prefab);
    loader.setComponents(value, _entity, this);
}

void Scene::addPrefab(std::string id, Json::Value components) {
    prefabs.emplace(id, components);
}

void Scene::clearPrefabs() { prefabs.clear(); }

ComponentsManager* Scene::getComponentsManager() { return componentManager; }

void Scene::clearComponentsManager() { componentManager->clearComponents(); }
void Scene::deleteComponents() { componentManager->deleteComponents(); }
void Scene::insertComponents() { componentManager->insertComponents(); }
