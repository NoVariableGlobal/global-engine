#pragma once
#include <SDL_events.h>
#include <map>
#include <string>

namespace Json {
    class Value;
}

class Entity;
class ComponentsManager;
class Game;

class Scene {
  private:
    // id, entity
    std::map<std::string, Entity*> entities;
    // id, components
    std::map<std::string, Json::Value> prefabs;

    ComponentsManager* componentManager;

    Game* game = nullptr;

  public:
    Scene(Game* _game);
    ~Scene();

    // calls to game->setScene()
    void changeScene(std::string _sceneName);

    // Given the name of the scene, reads its respective file and tells the
    // Engine to create all entities and component
    void load(std::string name);

    // update the scene
    void update();
    // render the entities of the scene
    void render();
    // handle the input of the game
    void handleInput(const SDL_Event& _event);

    // Search the entity in map and returns a reference to it.
    Entity* getEntitybyId(std::string id);
    // Add entity into the map.
    void addEntity(Entity* entity);

    // clear the entities of the map.
    void clearEntities();

    // returns a new instance of a prefab.
    Entity* getInstanceOf(std::string _prefab,
                          std::string _id, std::string _tag = "Default");
    // Search the prefab in the map and equals its info the entity
    void clonePrefabInfo(std::string _prefab, Entity* _entity);
    // Add prefab into the map.
    void addPrefab(std::string id, Json::Value components);
    // clear the entities of the map.
    void clearPrefabs();

    // Get ComponentsManager.
    ComponentsManager* getComponentsManager();
    // Clear the Components Manager
    void clearComponentsManager();
    // delete the components to delete
    void deleteComponents();
    // inserts components to insert
    void insertComponents();
};
