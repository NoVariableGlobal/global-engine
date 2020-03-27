#include "BulletEC.h"
#include "ComponentsManager.h"
#include "FactoriesFactory.h"
#include "Factory.h"
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

BulletEC::BulletEC() {}

BulletEC::~BulletEC() {}

void BulletEC::destroy() {
    setActive(false);
    scene->getComponentsManager()->eraseEC(this);
}

void BulletEC::checkEvent() {
    dynamic_cast<RigidbodyPC*>(father->getComponent("RigidbodyPC")).
}

void BulletEC::setDamage(float _d) { damage = _d; }

float BulletEC::getDamage() { return damage; }

// FACTORY INFRASTRUCTURE
class BulletECFactory final : public ComponentFactory {
  public:
    BulletECFactory() = default;

    Component* create(Entity* _father, Json::Value& _data,
                      Scene* _scene) override {

        BulletEC* bullet = new BulletEC();
        _scene->getComponentsManager()->addEC(bullet);

        bullet->setFather(_father);
        bullet->setScene(_scene);

        if (!_data["damage"].asDouble())
            throw std::exception("BulletEC: damage is not a double");
        bullet->setDamage(_data["damage"].isDouble());

        return bullet;
    };
};

REGISTER_FACTORY("BulletEC", BulletEC);