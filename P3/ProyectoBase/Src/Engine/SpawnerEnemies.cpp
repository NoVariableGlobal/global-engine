#include "SpawnerEnemies.h"
#include "Entity.h"
#include "TransformComponent.h"
#include "OgreVector3.h"
#include "Spawner.cpp"

void SpawnerEnemies::checkEvent()
{

  Entity* newEntity;
  if (timeToSpawn()) {
    newEntity = spawnPrefab();
    if(transform == nullptr)
      transform = static_cast<TransformComponent*> (father->getComponent("TransformComponent"));

    TransformComponent * spawnTransform = static_cast<TransformComponent*> (newEntity->getComponent("TransformComponent"));
    scene->addEntity(newEntity);
    spawnTransform->setPosition(transform->getPosition());
  }
}


// FACTORY INFRASTRUCTURE
class SpawnerEnemiesFactory : public SpawnerFactory {
public:
  SpawnerEnemiesFactory() {};
  virtual Component* create(Entity* _father, Json::Value& _data, Scene* scene)
  {
    return SpawnerFactory::create(_father, _data, scene);
  };
};

REGISTER_FACTORY("SpawnerEnemies", SpawnerEnemies);
