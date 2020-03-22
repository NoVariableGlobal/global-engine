#include "SpawnerPowerUpEC.h"
#include "ComponentsManager.h"
#include "Entity.h"
#include "FactoriesFactory.h"
#include "Scene.h"
#include "TransformComponent.h"

#include "Factory.h"
#include <json.h>

void SpawnerPowerUpEC::checkEvent() {
    if (timeToSpawn()) {
        Entity* newEntity = spawnPrefab();

        TransformComponent* spawnTransform = dynamic_cast<TransformComponent*>(
            newEntity->getComponent("TransformComponent"));
        spawnTransform->setPosition(transform->getPosition());
    }
}

void SpawnerPowerUpEC::setDuration(double _duration) { duration = _duration; }

void SpawnerPowerUpEC::setInstantaneous(bool _isInstant) {
    instantaneous = _isInstant;
}

// FACTORY INFRASTRUCTURE
class SpawnerPowerUpECFactory final : public ComponentFactory {
  public:
    SpawnerPowerUpECFactory() = default;

    Component* create(Entity* _father, Json::Value& _data,
                      Scene* scene) override {
        SpawnerPowerUpEC* spawnerPowerUpEC = new SpawnerPowerUpEC();

        spawnerPowerUpEC->setFather(_father);
        spawnerPowerUpEC->setScene(scene);
        scene->getComponentsManager()->addEC(spawnerPowerUpEC);

        if (!_data["spawnCooldown"].isDouble())
            throw std::exception("Spawner: spawnCooldown is not a double");
        spawnerPowerUpEC->setSpawnCooldown(_data["spawnCooldown"].asDouble());

        if (!_data["spawnID"].isArray())
            throw std::exception("Spawner: spawnID is not an array");
        else if (!_data["spawnID"][0].isString())
            throw std::exception("Spawner: spawnID is not an array of strings");

        if (!_data["spawnChances"].isArray())
            throw std::exception("Spawner: spawnChances is not an array");
        else if (!_data["spawnChances"][0].isDouble())
            throw std::exception(
                "Spawner: spawnChances is not an array of doubles");

        if (!_data["duration"].isArray())
            throw std::exception("Spawner: duration is not an array");
        else if (!_data["duration"][0].isDouble())
            throw std::exception(
                "Spawner: duration is not an array of doubles");

        if (!_data["isInstant"].isArray())
            throw std::exception("Spawner: isInstant is not an array");
        else if (!_data["isInstant"][0].isBool())
            throw std::exception(
                "Spawner: isInstant is not an array of booleans");

        spawnerPowerUpEC->setActive(true);

        return spawnerPowerUpEC;
    };
};

REGISTER_FACTORY("SpawnerPowerUpEC", SpawnerPowerUpEC);
