#include "SpawnerFloorRandomEC.h"
#include "Entity.h"
//#include "FloorComponent.h"
#include "TransformComponent.h"
#include "OgreVector3.h"
#include "FactoriesFactory.h"
#include "Scene.h"
#include "ComponentsManager.h"

#include "Factory.h"
#include <json.h>


void SpawnerFloorRandomEC::checkEvent()
{
  /*if (first) {
    first = false;
    floorDimensions = staticCast<FloorComponent*>(father->getComponent("FloorComponent"))->getDimensions();
  }*/

  if (timeToSpawn()) {
    Entity* newEntity = spawnPrefab();

    TransformComponent* spawnTransform = static_cast<TransformComponent*> (newEntity->getComponent("TransformComponent"));

    float x = floorDimensions.x + static_cast <float> (rand()) / static_cast <float> (RAND_MAX) * floorDimensions.z;
    float z = floorDimensions.y + static_cast <float> (rand()) / static_cast <float> (RAND_MAX) * floorDimensions.w;
    spawnTransform->setPosition(Ogre::Vector3(x, static_cast<TransformComponent*>(father->getComponent("TransformComponent"))->getPosition().y, z));
  }
}


// FACTORY INFRASTRUCTURE
class SpawnerFloorRandomECFactory : public ComponentFactory {
public:
  SpawnerFloorRandomECFactory() {};
  virtual Component* create(Entity* _father, Json::Value& _data, Scene* scene)
  {
    SpawnerFloorRandomEC* spawnerFloorRandomEC = new SpawnerFloorRandomEC();

    spawnerFloorRandomEC->setFather(_father);
    scene->getComponentsManager()->addEC(spawnerFloorRandomEC);

    if (!_data["spawnCooldown"].isDouble()) throw std::exception("Spawner: spawnCooldown is not a double");
    spawnerFloorRandomEC->setSpawnCooldown(_data["spawnCooldown"].asDouble());
    if (!_data["spawnID"].isArray()) throw std::exception("Spawner: spawnID is not an array");
    else if (!_data["spawnID"][0].isString()) throw std::exception("Spawner: spawnID is not an array of strings");
    if (!_data["spawnChances"].isArray()) throw std::exception("Spawner: spawnChances is not an array");
    else if (!_data["spawnChances"][0].isDouble()) throw std::exception("Spawner: spawnChances is not an array of doubles");
    for (int i = 0; i < _data["spawnID"].size(); ++i) {
      if (!spawnerFloorRandomEC->addSpawn(_data["spawnID"][i].asString(), _data["spawnChances"][i].asDouble())) {
        printf(("No se pudo a�adir " + _data["spawnID"][i].asString() + ": Ya se lleg� al 100% de probabilidad./n").c_str());
        break;
      }
    }

    spawnerFloorRandomEC->setActive(true);

    return spawnerFloorRandomEC;
  };
};

REGISTER_FACTORY("SpawnerFloorRandomEC", SpawnerFloorRandomEC);