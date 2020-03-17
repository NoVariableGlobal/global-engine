#include "SpawnerEnemiesEC.h"
#include "Entity.h"
#include "TransformComponent.h"
#include "OgreVector3.h"
#include "FactoriesFactory.h"
#include "Scene.h"
#include "ComponentsManager.h"

#include "Factory.h"
#include <json.h>

void SpawnerEnemiesEC::checkEvent()
{
  if (timeToSpawn()) {
    Entity* newEntity = spawnPrefab();

    TransformComponent* spawnTransform = dynamic_cast<TransformComponent*> (newEntity->getComponent("TransformComponent"));
    spawnTransform->setPosition(transform->getPosition());
  }
}

void SpawnerEnemiesEC::setTransform(TransformComponent* trans)
{
    transform = trans;
}


// FACTORY INFRASTRUCTURE
class SpawnerEnemiesECFactory : public ComponentFactory {
public:
  SpawnerEnemiesECFactory() {};
  virtual Component* create(Entity* _father, Json::Value& _data, Scene* scene)
  {
    SpawnerEnemiesEC* spawnerEnemies = new SpawnerEnemiesEC();

    spawnerEnemies->setFather(_father);
    spawnerEnemies->setScene(scene);

    spawnerEnemies->setTransform(dynamic_cast<TransformComponent*>(_father->getComponent("TransformComponent")));
    scene->getComponentsManager()->addEC(spawnerEnemies);

    if (!_data["spawnCooldown"].isDouble()) throw std::exception("Spawner: spawnCooldown is not a double");
        spawnerEnemies->setSpawnCooldown(_data["spawnCooldown"].asDouble());
    if (!_data["spawnID"].isArray()) throw std::exception("Spawner: spawnID is not an array");
    else if (!_data["spawnID"][0].isString()) throw std::exception("Spawner: spawnID is not an array of strings");

    if (!_data["spawnChances"].isArray()) throw std::exception("Spawner: spawnChances is not an array");
    else if (!_data["spawnChances"][0].isDouble()) throw std::exception("Spawner: spawnChances is not an array of doubles");

    for (int i = 0; i < _data["spawnID"].size(); ++i) {
      if (!spawnerEnemies->addSpawn(_data["spawnID"][i].asString(), _data["spawnChances"][i].asDouble())) {
        printf(("No se pudo añadir " + _data["spawnID"][i].asString() + ": Ya se llegó al 100% de probabilidad./n").c_str());
        break;
      }
    }

    spawnerEnemies->setActive(true);

    return spawnerEnemies;
  };
};

REGISTER_FACTORY("SpawnerEnemiesEC", SpawnerEnemiesEC);