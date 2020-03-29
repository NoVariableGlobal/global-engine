#include "SpawnerFloorRandomEC.h"
#include "Entity.h"
//#include "FloorComponent.h"
#include "ComponentsManager.h"
#include "FactoriesFactory.h"
#include "Factory.h"
#include "OgreVector3.h"
#include "RigidbodyPC.h"
#include "Scene.h"
#include "TransformComponent.h"
#include <iostream>
#include <json.h>

void SpawnerFloorRandomEC::setFloorDimensions(Ogre::Vector4f _floorDimensions) {
    floorDimensions = _floorDimensions;
}

void SpawnerFloorRandomEC::destroy() {
    setActive(false);
    scene->getComponentsManager()->eraseEC(this);
}

void SpawnerFloorRandomEC::checkEvent() {

    if (firstTime) {
        firstTime = false;
        _lastTimeSpawned = clock() / static_cast<float>(CLOCKS_PER_SEC);
    }

    // Spawnea un prefab en una posicion random del mapa cada cierto tiempo
    if (timeToSpawn()) {
        Entity* newEntity = spawnPrefab();

        TransformComponent* spawnTransform = static_cast<TransformComponent*>(
            newEntity->getComponent("TransformComponent"));
        RigidbodyPC* rigidbody =
            static_cast<RigidbodyPC*>(newEntity->getComponent("RigidbodyPC"));

        float x = floorDimensions.x + static_cast<float>(rand()) /
                                          static_cast<float>(RAND_MAX) *
                                          floorDimensions.z;
        float z = floorDimensions.y + static_cast<float>(rand()) /
                                          static_cast<float>(RAND_MAX) *
                                          floorDimensions.w;
        spawnTransform->setPosition(Ogre::Vector3(x, 0, z));
        rigidbody->setPosition(Ogre::Vector3(x, 0, z));
    }
}

// FACTORY INFRASTRUCTURE
class SpawnerFloorRandomECFactory final : public ComponentFactory {
  public:
    SpawnerFloorRandomECFactory() = default;

    Component* create(Entity* _father, Json::Value& _data,
                      Scene* scene) override {
        SpawnerFloorRandomEC* spawnerFloorRandomEC = new SpawnerFloorRandomEC();
        scene->getComponentsManager()->addEC(spawnerFloorRandomEC);

        spawnerFloorRandomEC->setFather(_father);
        spawnerFloorRandomEC->setScene(scene);

        // X and Y are the starting position and Z and W are the maximum that
        // position can be modified
        if (!_data["floorDimensions[x,y,z,w]"].isArray())
            throw std::exception("random[x,y,z,w]: position is not an array");
        spawnerFloorRandomEC->setFloorDimensions(
            Ogre::Vector4f(_data["floorDimensions[x,y,z,w]"][0].asFloat(),
                           _data["floorDimensions[x,y,z,w]"][1].asFloat(),
                           _data["floorDimensions[x,y,z,w]"][2].asFloat(),
                           _data["floorDimensions[x,y,z,w]"][3].asFloat()));

        if (!_data["spawnCooldown"].isDouble())
            throw std::exception("Spawner: spawnCooldown is not a double");
        spawnerFloorRandomEC->setSpawnCooldown(
            _data["spawnCooldown"].asDouble());

        if (!_data["spawnID"].isArray())
            throw std::exception("Spawner: spawnID is not an array");
        else if (!_data["spawnID"][0].isString())
            throw std::exception("Spawner: spawnID is not an array of strings");

        if (!_data["spawnTag"].isString())
            throw std::exception("Spawner: spawnTag is not a string");
        std::string tag = _data["spawnTag"].asString();

        if (!_data["spawnChances"].isArray())
            throw std::exception("Spawner: spawnChances is not an array");
        else if (!_data["spawnChances"][0].isDouble())
            throw std::exception(
                "Spawner: spawnChances is not an array of doubles");

        for (int i = 0; i < _data["spawnID"].size(); ++i) {
            if (!spawnerFloorRandomEC->addSpawn(
                    _data["spawnID"][i].asString(),
                    _data["spawnChances"][i].asDouble(), tag)) {
                printf(("No se pudo aniadir " + _data["spawnID"][i].asString() +
                        ": Ya se llego al 100% de probabilidad./n")
                           .c_str());
                break;
            }
        }

        spawnerFloorRandomEC->setActive(true);

        return spawnerFloorRandomEC;
    };
};

REGISTER_FACTORY("SpawnerFloorRandomEC", SpawnerFloorRandomEC);
