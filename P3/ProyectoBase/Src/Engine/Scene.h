#pragma once
#include <map>
#include <vector>
#include <string>
#include "checkML.h"

class Component;
class Entity;
class ComponentsManager;

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

      void update();

      // Search the entity in map and returns a reference to it.
      Entity* getEntitybyId(std::string id);

      // Clear the Components Manager
      void clearComponentsManager();
};
