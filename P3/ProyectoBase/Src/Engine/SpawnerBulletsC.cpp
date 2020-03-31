#include "SpawnerBulletsC.h"

#include "ComponentsManager.h"
#include "Entity.h"
#include "FactoriesFactory.h"
#include "Scene.h"

#include <json.h>

SpawnerBulletsC::SpawnerBulletsC() {}

SpawnerBulletsC::~SpawnerBulletsC() {}


void SpawnerBulletsC::destroy() {
    setActive(false);
    scene->getComponentsManager()->eraseDC(this);
}

Entity* SpawnerBulletsC::getBullet(std::string _type, std::string _tag) { 
    return scene->getInstanceOf(_type, _type + std::to_string(count++), _tag);
}


// FACTORY INFRASTRUCTURE
SpawnerBulletsCFactory::SpawnerBulletsCFactory(){};
Component* SpawnerBulletsCFactory::create(Entity* _father, Json::Value& _data,
                                        Scene* _scene) {
    SpawnerBulletsC* spawner = new SpawnerBulletsC();
    _scene->getComponentsManager()->addDC(spawner);

    spawner->setFather(_father);
    spawner->setScene(_scene);

    return spawner;
};

DEFINE_FACTORY(SpawnerBulletsC);
