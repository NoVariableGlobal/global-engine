#include "SpawnerFloorRandomEC.h"
#include "Entity.h"
//#include "FloorComponent.h"
#include "TransformComponent.h"
#include "OgreVector3.h"
#include "Spawner.cpp"

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
class SpawnerFloorRandomFactory : public SpawnerFactory {
public:
  SpawnerFloorRandomFactory() {};
  virtual Component* create(Entity* _father, Json::Value& _data, Scene* scene)
  {
    return SpawnerFactory::create(_father, _data, scene);
  };
};

REGISTER_FACTORY("SpawnerFloorRandom", SpawnerFloorRandom);