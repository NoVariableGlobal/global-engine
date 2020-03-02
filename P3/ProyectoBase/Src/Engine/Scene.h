#pragma once
#include <map>
#include <vector>
#include <string>
class string;
class Component;
class Entity;


typedef std::string Id;

class Scene {

  std::map<Id*, Entity*> entities;

public:
  Scene();
  ~Scene();


  // Given the name of the scene, reads its respective file and tells the Engine to create all entities and component
  void load(std::string name);


  //void update();

  // Search the entity in map and returns a reference to it.
  Entity* getEntitybyId(Id id);
};
