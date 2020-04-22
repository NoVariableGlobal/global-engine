#include "Scene.h"
#include "Component.h"
#include "ComponentsManager.h"
#include "Entity.h"
#include "Game.h"
#include "Loader.h"
#include "PhysicsContext.h"
#include "Util.h"
#include <json.h>

Scene::Scene(Game* game) {
    componentManager_ = new ComponentsManager();

    PhysicsContext::getInstance()->init(0.0f);

    Loader loader;
    loader.readPrefabs(this);

    game_ = game;
}

Scene::~Scene() {
    clearEntities();
    clearPrefabs();

    delete componentManager_;
    PhysicsContext::getInstance()->destroyWorld();
}

void Scene::changeScene(const std::string& sceneName, const bool deleteAll) {
    game_->setChangeScene(true, sceneName, deleteAll);
}

void Scene::load(const std::string& name) {
    Loader loader;
    loader.readObjects(name, this);
}

void Scene::update() {
    componentManager_->update();
    componentManager_->updateEvent();
    componentManager_->updateSound();

    PhysicsContext::getInstance()->updateSimulation();
}

void Scene::render() { componentManager_->render(); }

void Scene::handleInput(const SDL_Event& _event) {
    componentManager_->handleInput(_event);
}

Entity* Scene::getEntityById(const std::string& id) const {
    return assert_find(entities_, id);
}

std::vector<Entity*> Scene::getEntitiesByTag(const std::string tag) {
    std::vector<Entity*> tagEntities;

    for (auto it : entities_) {
        if (it.second->getTag() == tag) {
            tagEntities.push_back(it.second);
        }
    }

    return tagEntities;
}

void Scene::addEntity(Entity* entity) {
    entities_.emplace(entity->getId(), entity);
}

std::map<std::string, Entity*>::iterator Scene::deleteEntity(Entity* entity) {
    std::map<std::string, Component*>& components = entity->getAllComponents();
    for (auto it : components) {
        it.second->destroy();
    }

    const std::string id = entity->getId();
    delete entities_.find(id)->second;
    return entities_.erase(entities_.find(id));
}

void Scene::clearEntities() {
    for (auto it : entities_) {
        delete it.second;
    }

    entities_.clear();
}

void Scene::clearNonPersistentEntities() {
    auto it = entities_.begin();
    while (it != entities_.end()) {
        if (!it->second->isPersistent())
            it = deleteEntity(it->second);
        else
            ++it;
    }
}

Entity* Scene::getInstanceOf(const std::string& prefab, const std::string& id,
                             const std::string& tag) {
    Entity* instance = new Entity();

    instance->setId(id);
    instance->setTag(tag);

    clonePrefabInfo(prefab, instance);

    entities_.emplace(instance->getId(), instance);

    return instance;
}

void Scene::clonePrefabInfo(const std::string& prefab, Entity* entity) {
    Loader loader;
    Json::Value value = assert_find(prefabs_, prefab);
    loader.setComponents(value, entity, this);
}

void Scene::addPrefab(const std::string& id, const Json::Value& components) {
    prefabs_.emplace(id, components);
}

void Scene::clearPrefabs() { prefabs_.clear(); }

ComponentsManager* Scene::getComponentsManager() const {
    return componentManager_;
}

void Scene::clearComponentsManager() { componentManager_->clearComponents(); }
void Scene::deleteComponents() { componentManager_->deleteComponents(); }
void Scene::insertComponents() { componentManager_->insertComponents(); }

Game* Scene::getGame() { return game_; }
