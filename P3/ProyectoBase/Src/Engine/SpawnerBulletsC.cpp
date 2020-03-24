#include "SpawnerBulletsC.h"

#include "ComponentsManager.h"
#include "FactoriesFactory.h"
#include "Factory.h"
#include "Scene.h"
#include "Entity.h"

#include <json.h>

SpawnerBulletsC::SpawnerBulletsC() {}

SpawnerBulletsC::~SpawnerBulletsC() {}

void SpawnerBulletsC::destroyMyself() {
    setActive(false);
    scene->getComponentsManager()->eraseDC(this);
}

Entity* SpawnerBulletsC::getBullet(std::string _type) { 
    return scene->getInstanceOf(_type, _type + std::to_string(count++));
}

// FACTORY INFRASTRUCTURE
class SpawnerBulletsCFactory : public ComponentFactory {
  public:
    SpawnerBulletsCFactory(){};
    virtual Component* create(Entity* _father, Json::Value& _data,
                              Scene* _scene) {
        SpawnerBulletsC* spawner = new SpawnerBulletsC();
        _scene->getComponentsManager()->addDC(spawner);

        spawner->setFather(_father);
        spawner->setScene(_scene);

        return spawner;
    };
};

REGISTER_FACTORY("SpawnerBulletsC", SpawnerBulletsC);
