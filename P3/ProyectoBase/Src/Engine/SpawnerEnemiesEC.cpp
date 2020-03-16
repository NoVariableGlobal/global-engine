#include "SpawnerEnemiesEC.h"
#include "Scene.h"
#include "Entity.h"
#include "TransformComponent.h"
#include "OgreVector3.h"
#include "FactoriesFactory.h"
#include "Factory.h"
#include "ComponentsManager.h"

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
        scene->getComponentsManager()->addEC(spawnerEnemies);
        
        spawnerEnemies->setFather(_father);
        spawnerEnemies->setScene(scene);

        spawnerEnemies->setTransform(dynamic_cast<TransformComponent*> (_father->getComponent("TransformComponent")));
        
		return spawnerEnemies;
	}
};

REGISTER_FACTORY("SpawnerEnemiesEC", SpawnerEnemiesEC);