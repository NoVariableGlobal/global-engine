#pragma once
#include <map>
#include <vector>

class string;
class Component;
class Entity;


typedef string Id;

class Scene {

  std::map<Id*, Entity*> entities;
  std::vector<Component*> componentList;

public:
  Scene();
  ~Scene();


  void load(string name);
  void update();
};