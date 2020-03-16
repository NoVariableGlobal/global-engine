#include "SpawnerFloorRandom.h"
#include "Entity.h"
//#include "FloorComponent.h"
#include "TransformComponent.h"
#include "Scene.h"
#include "OgreVector3.h"

void SpawnerFloorRandom::checkEvent()
{
  /*if (first) {
    first = false;
    floorDimensions = staticCast<FloorComponent*>(father->getComponent("FloorComponent"))->getDimensions();
  }*/

  Entity* newEntity;
  if (timeToSpawn()) {
    newEntity = spawnPrefab();

    TransformComponent* spawnTransform = static_cast<TransformComponent*> (newEntity->getComponent("TransformComponent"));
    scene->addEntity(newEntity);


    float x = floorDimensions.x + static_cast <float> (rand()) / static_cast <float> (RAND_MAX) * floorDimensions.z;
    float z = floorDimensions.y + static_cast <float> (rand()) / static_cast <float> (RAND_MAX) * floorDimensions.w;
    spawnTransform->setPosition(Ogre::Vector3(x, static_cast<TransformComponent*>(father->getComponent("TransformComponent"))->getPosition().y, z));
  }
}
