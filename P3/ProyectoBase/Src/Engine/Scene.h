#pragma once
#include <map>
#include <vector>
#include <string>
#include <SDL_events.h>

namespace Json 
{
    class Value;
}

class Component;
class Entity;
class ComponentsManager;
class CameraObject;

class Scene 
{
    private:
      // id, entity
      std::map<std::string, Entity*> entities;
      // id, components
      std::map<std::string, Json::Value> prefabs;

      ComponentsManager* componentManager;
  
    public:
      Scene();
      ~Scene();

      // Given the name of the scene, reads its respective file and tells the Engine to create all entities and component
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

      // Search the prefab in the map and returns a new instance of it.
      Entity* getInstanceOf(std::string id, int num = NULL);
      // Add prefab into the map.
      void addPrefab(std::string id, Json::Value components);
      // clear the entities of the map.
      void clearPrefabs();

      // Get ComponentsManager.
      ComponentsManager* getComponentsManager();
      // Clear the Components Manager
      void clearComponentsManager();
};
