#include "SpawnerEC.h"
#include "ComponentsManager.h"
#include "Entity.h"
#include "FactoriesFactory.h"
#include "Factory.h"
#include "Scene.h"
#include <time.h>
#include <utility>
#include <value.h>

bool SpawnerEC::addSpawn(std::string id, float chance) {
    float totalChance = 0;
    if (_spawns.size() != 0)
        totalChance = _spawns.back()._additiveChance;
    if (totalChance > 99.999)
        return false;
    _spawns.push_back({id, chance, totalChance + chance});

    if (_spawns.back()._additiveChance > 99.999)
        _spawns.back()._additiveChance = 100;

    return true;
}

void SpawnerEC::editChance(std::string& id, float newChance) {
    size_t i = 0;
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

void SpawnerEC::checkEvent() {
    if (firstTime) {
        firstTime = false;
        _lastTimeSpawned = clock() / static_cast<float>(CLOCKS_PER_SEC);
    }

    if (timeToSpawn()) {
        spawnPrefab();
    }
}

bool SpawnerEC::timeToSpawn() {
    float seconds = clock() / static_cast<float>(CLOCKS_PER_SEC);

    if (seconds - _lastTimeSpawned >= _spawnCooldown) {
        _lastTimeSpawned = seconds;
        return true;
    }

    return false;
}

Entity* SpawnerEC::spawnPrefab() {
    Spawn toInstantiate;

    while (toInstantiate._id == "") {
        float random =
            static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 100;
        toInstantiate = binarySearch(0, _spawns.size() - 1, random);
    }
    return scene->getInstanceOf(toInstantiate._id,
                                toInstantiate._id + std::to_string(_count++));
}

Spawn SpawnerEC::binarySearch(int first, int last, float value) {
    if (last >= first) {
        int center = first + (last - first) / 2;

        if (_spawns[center]._additiveChance >= value &&
            (center == 0 || _spawns[center - 1]._additiveChance < value))
            return _spawns[center];

        if (_spawns[center]._additiveChance < value)
            return binarySearch(center + 1, last, value);

        return binarySearch(first, center - 1, value);
    }

    return {"", 0, 0};
}

// FACTORY INFRASTRUCTURE
class SpawnerECFactory final : public ComponentFactory {
  public:
    SpawnerECFactory() = default;

    Component* create(Entity* _father, Json::Value& _data,
                      Scene* scene) override {
        SpawnerEC* spawnerEC = new SpawnerEC();

        spawnerEC->setFather(_father);
        scene->getComponentsManager()->addEC(spawnerEC);

        if (!_data["spawnCooldown"].isDouble())
            throw std::exception("Spawner: spawnCooldown is not a double");
        spawnerEC->setSpawnCooldown(_data["spawnCooldown"].asDouble());
        if (!_data["spawnID"].isArray())
            throw std::exception("Spawner: spawnID is not an array");
        if (!_data["spawnID"][0].isString())
            throw std::exception("Spawner: spawnID is not an array of strings");
        if (!_data["spawnChances"].isArray())
            throw std::exception("Spawner: spawnChances is not an array");
        if (!_data["spawnChances"][0].isDouble())
            throw std::exception(
                "Spawner: spawnChances is not an array of doubles");
        for (int i = 0; i < _data["spawnID"].size(); ++i) {
            if (!spawnerEC->addSpawn(_data["spawnID"][i].asString(),
                                     _data["spawnChances"][i].asDouble())) {
                printf(("No se pudo añadir " + _data["spawnID"][i].asString() +
                        ": Ya se llegó al 100% de probabilidad./n")
                           .c_str());
                break;
            }
        }

        spawnerEC->setActive(true);

        return spawnerEC;
    };
};

REGISTER_FACTORY("SpawnerEC", SpawnerEC);
