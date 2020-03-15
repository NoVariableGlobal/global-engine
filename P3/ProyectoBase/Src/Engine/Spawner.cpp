#include "Spawner.h"
#include <utility>
#include "Scene.h"
#include <time.h>

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

void Spawner::update()
{
  float seconds = clock() / (float) CLOCKS_PER_SEC;


}

bool Spawner::timeToSpawn()
{
  return false;
}
