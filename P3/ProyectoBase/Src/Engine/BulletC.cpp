#include "BulletC.h"
#include "ComponentsManager.h"
#include "FactoriesFactory.h"
#include "Scene.h"
#include "Entity.h"
#include "TransformComponent.h"
#include "OgreRoot.h"
#include "RigidbodyPC.h"
#include "TridimensionalObjectRC.h"

#include <time.h>
#include <utility>
#include <value.h>
#include <json.h>

BulletC::BulletC() {}

BulletC::~BulletC() {}

void BulletC::destroy() {
    setActive(false);
    scene->getComponentsManager()->eraseDC(this);
}

void BulletC::setDamage(float _d) { damage = _d; }

float BulletC::getDamage() { return damage; }

void BulletC::dealCollision() { scene->deleteEntity(father); }

// FACTORY INFRASTRUCTURE
BulletCFactory::BulletCFactory() = default;

    Component* BulletCFactory::create(Entity* _father, Json::Value& _data,
                      Scene* _scene)  {

        BulletC* bullet = new BulletC();
        _scene->getComponentsManager()->addDC(bullet);

        bullet->setFather(_father);
        bullet->setScene(_scene);

        return bullet;
    };

DEFINE_FACTORY(BulletC);