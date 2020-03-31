#include "SniperBulletC.h"
#include "Scene.h"
#include "ComponentsManager.h"
#include <json.h>
#include "FactoriesFactory.h"

void SniperBulletC::dealCollision() {}

// FACTORY INFRASTRUCTURE
SniperBulletCFactory::SniperBulletCFactory() = default;

    Component* SniperBulletCFactory::create(Entity* _father, Json::Value& _data,
                      Scene* _scene) {

        SniperBulletC* bullet = new SniperBulletC();
        _scene->getComponentsManager()->addDC(bullet);

        bullet->setFather(_father);
        bullet->setScene(_scene);

        return bullet;
    };

DEFINE_FACTORY(SniperBulletC);