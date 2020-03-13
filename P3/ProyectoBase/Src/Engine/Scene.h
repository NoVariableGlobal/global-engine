#pragma once
#include <map>
#include <vector>
#include <string>

#include "checkML.h"

#include <SDL_events.h>

class Component;
class Entity;
class ComponentsManager;
class CameraObject;

class Scene 
{
    private:
      std::map<std::string, Entity*> entities; 
      bool exit = false;
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

      // Clear the Components Manager
      void clearComponentsManager();
};
