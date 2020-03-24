#pragma once
#include "EventComponent.h"
#include <string>
#include <vector>

class Entity;

struct Spawn {
    std::string _id;
    float _chance;
    float _additiveChance;
};

class SpawnerEC : public EventComponent {
  private:
    int _count = 0;

  protected:
    Spawn mySpawn;

    std::vector<Spawn> _spawns;
    float _spawnCooldown = 0;
    float _lastTimeSpawned = 0;
    bool firstTime = true;


  public:
    void setSpawnCooldown(float spawnCooldown) {
        _spawnCooldown = spawnCooldown;
    }
    /*
    Adds a prefab's id and its individual chance for spawning. If the total
    chance after adding this spawn is greater than 100%, the last spawn will
    only have the minimal chance to reach a total of 100%.

    @param id: prefab's Id.
    @param chance: individual chance of the spawn, in percentage.
    @return true if the spawn could be added, false if the spawn could not be
    added. The total chance was already 100%.
    */
    virtual void destroyMyself();
    bool addSpawn(std::string id, float chance);

    /*
    Changes the individual chance of an already added spawn. If the id was not
    originally in the spawner, it will be added instead.

    @param id: prefab's Id.
    @param newChance: new individual chance of the spawn, in percentage.
    */
    void editChance(std::string& id, float newChance);

    virtual void checkEvent() override;

    bool timeToSpawn();

    Entity* spawnPrefab();

    Spawn binarySearch(int first, int last, float value);
};
