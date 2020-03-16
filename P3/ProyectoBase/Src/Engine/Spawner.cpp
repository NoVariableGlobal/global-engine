#include "Spawner.h"
#include <utility>
#include "Scene.h"
#include <time.h>
#include "Entity.h"

bool Spawner::addSpawn(std::string& id, float chance)
{
  float totalChance = _spawns.back()._additiveChance;
  if (totalChance > 99.999)
    return false;
  _spawns.push_back({ id, chance, totalChance + chance });

  if (_spawns.back()._additiveChance > 99.999)
    _spawns.back()._additiveChance = 100;

  return true;
}

void Spawner::editChance(std::string& id, float newChance)
{
  int i = 0;
  bool found = false;
  float totalChance;
  for (; i < _spawns.size(); ++i) {
    if (!found)
      found = id == _spawns[i]._id;
    else {
      _spawns[i - 1]._id.swap(_spawns[i]._id);
      std::swap(_spawns[i - 1], _spawns[i]);
      totalChance = _spawns[i - 1]._additiveChance -= _spawns[i]._chance;
    }
  }

  if (!found) {
    addSpawn(id, newChance);
    return;
  }

  _spawns.back()._chance = newChance;

  _spawns.back()._additiveChance = totalChance + newChance;

  if (_spawns.back()._additiveChance > 99.999)
    _spawns.back()._additiveChance = 100;
}

void Spawner::checkEvent()
{
  Entity* newEntity;
  if (timeToSpawn()) {
    newEntity = spawnPrefab();
    scene->addEntity(newEntity);
  }
}

bool Spawner::timeToSpawn()
{
  float seconds = clock() / static_cast <float> (CLOCKS_PER_SEC);

  if (seconds - _lastTimeSpawned >= _spawnCooldown) {
    _lastTimeSpawned = seconds;
    return true;
  }

  return false;
}

Entity * Spawner::spawnPrefab()
{
  Spawn toInstantiate;
  
  while (toInstantiate._id == "") {
    float random = static_cast <float> (rand()) / static_cast <float> (RAND_MAX) * 100;
    toInstantiate = binarySearch(0, _spawns.size() - 1, random);
  }
  return scene->getInstanceOf(toInstantiate._id, toInstantiate._count++);
}

Spawn Spawner::binarySearch(int first, int last, float value)
{
  if (last >= first) {
    int center = first + (last - first) / 2;
    
    if (_spawns[center]._additiveChance >= value && (center == 0 || _spawns[center - 1]._additiveChance < value)) 
      return _spawns[center];
    
 
    if (_spawns[center]._additiveChance < value)
      return binarySearch(center+1, last, value);

    return binarySearch(first, center-1, value);
  }

  return {"", 0, 0};
}


