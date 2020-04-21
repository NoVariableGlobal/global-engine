#pragma once
#include <SDL_events.h>
#include <map>
#include <string>
#include <vector>

namespace Json {
    class Value;
}

class Entity;
class ComponentsManager;
class Game;

class Scene {
    // id, entity
    std::map<std::string, Entity*> entities_;
    // id, components
    std::map<std::string, Json::Value> prefabs_;

    ComponentsManager* componentManager_;

    Game* game_ = nullptr;

  public:
    Scene(Game* game);
    ~Scene();

    // calls to game->setScene()
    void changeScene(const std::string& sceneName, bool deleteAll = false);

    // Given the name of the scene, reads its respective file and tells the
    // Engine to create all entities and component
    void load(const std::string& name);

    // update the scene
    void update();
    // render the entities of the scene
    void render();
    // handle the input of the game
    void handleInput(const SDL_Event& _event);

    // Search the entity in map and returns a reference to it.
    Entity* getEntityById(const std::string& id) const;
    // Search entities in map and returns references to them.
    std::vector<Entity*> getEntitiesByTag(std::string tag);
    // Add entity into the map.
    void addEntity(Entity* entity);
    // Delete entity
    std::map<std::string, Entity*>::iterator deleteEntity(Entity* entity);
    // clear the entities of the map.
    void clearEntities();
    // clear the non scene persistant elements of the map.
    void clearNonPersistentEntities();

    // returns a new instance of a prefab.
    Entity* getInstanceOf(const std::string& prefab, const std::string& id,
                          const std::string& tag = "Default");
    // Search the prefab in the map and equals its info the entity
    void clonePrefabInfo(const std::string& prefab, Entity* entity);
    // Add prefab into the map.
    void addPrefab(const std::string& id, const Json::Value& components);
    // clear the entities of the map.
    void clearPrefabs();

    // Get ComponentsManager.
    ComponentsManager* getComponentsManager() const;
    // Clear the Components Manager
    void clearComponentsManager();
    // delete the components to delete
    void deleteComponents();
    // inserts components to insert
    void insertComponents();
};
