#pragma once
#include "EventComponent.h"
#include <vector>
#include <string>

class Entity;

class Spawner :
  public EventComponent
{
protected:

  struct Spawn
  {
    std::string _id;
    float _chance;
    float _additiveChance;
    unsigned int _count = 0;
  };

  std::vector<Spawn> _spawns;
  float _spawnCooldown;
  float _lastTimeSpawned;

public:
  /*
  Adds a prefab's id and its individual chance for spawning. If the total chance after adding this spawn 
  is greater than 100%, the last spawn will only have the minimal chance to reach a total of 100%.
  
  @param id: prefab's Id.
  @param chance: individual chance of the spawn, in percentage.
  @return true if the spawn could be added, false if the spawn could not be added. The total chance was 
  already 100%.
  */
  bool addSpawn(std::string& id, float chance);

  /*
  Changes the individual chance of an already added spawn. If the id was not originally in the spawner, 
  it will be added instead.

  @param id: prefab's Id.
  @param newChance: new individual chance of the spawn, in percentage.
  */
  void editChance(std::string& id, float newChance);

  virtual void checkEvent() override;

  bool timeToSpawn();

  Entity* spawnPrefab();

  Spawn binarySearch(int first, int last, float value);


};

