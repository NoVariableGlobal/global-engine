#include "SpawnerEnemies.h"
#include "Scene.h"
#include "Entity.h"
#include "TransformComponent.h"
#include "OgreVector3.h"

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
