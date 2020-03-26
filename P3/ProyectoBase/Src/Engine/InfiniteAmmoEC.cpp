#include "InfiniteAmmoEC.h"
#include "ComponentsManager.h"
#include "Entity.h"
#include "FactoriesFactory.h"
#include "Factory.h"
#include "GunC.h"
#include "LifeC.h"
#include "OgreVector3.h"
#include "RigidbodyPC.h"
#include "Scene.h"
#include "TransformComponent.h"
#include "TridimensionalObjectRC.h"
#include "WeaponControllerIC.h"
#include <iostream>
#include <json.h>

InfiniteAmmoEC::InfiniteAmmoEC() {}

InfiniteAmmoEC::~InfiniteAmmoEC() {}

void InfiniteAmmoEC::destroy() {
    setActive(false);
    scene->getComponentsManager()->eraseEC(this);
}

void InfiniteAmmoEC::checkEvent() {
    PowerUpEC::checkEvent();

    if (!picked && getCollisionWithPlayer()) {
        auto weaponController = dynamic_cast<WeaponControllerIC*>(
            father->getComponent("WeaponControllerIC"));
        GunC* gun = weaponController->getCurrentGun();
        gun->setInfiniteAmmo(true);
        picked = true;

        dynamic_cast<TridimensionalObjectRC*>(
            father->getComponent("TridimensionalObjectRC"))
            ->setActive(false);

        dynamic_cast<RigidbodyPC*>(father->getComponent("RigidbodyPC"))
            ->setActive(false);

        dynamic_cast<TransformComponent*>(
            father->getComponent("TransformComponent"))
            ->setActive(false);
    }
    if (!picked) { // delete item when the effect has passed
        if (timeDisappear()) {
            scene->deleteEntity(father);
        }
    } else if (timeDisappearEffect()) { // delete item when the effect has
                                        // passed
        auto weaponController = dynamic_cast<WeaponControllerIC*>(
            father->getComponent("WeaponControllerIC"));
        GunC* gun = weaponController->getCurrentGun();
        gun->setInfiniteAmmo(false);

        scene->deleteEntity(father);
    }
}

void InfiniteAmmoEC::setTimeEffect(float _time) { timeEffect = _time; }

bool InfiniteAmmoEC::timeDisappearEffect() {
    float seconds = clock() / static_cast<float>(CLOCKS_PER_SEC);

    if (!startPicked) {
        time = seconds;
        startPicked = true;
    }

    return time + timeEffect <= seconds;
}

// FACTORY INFRASTRUCTURE
class InfiniteAmmoECFactory final : public ComponentFactory {
  public:
    InfiniteAmmoECFactory() = default;

    Component* create(Entity* _father, Json::Value& _data,
                      Scene* scene) override {
        InfiniteAmmoEC* infiniteAmmo = new InfiniteAmmoEC();

        infiniteAmmo->setFather(_father);
        infiniteAmmo->setScene(scene);
        scene->getComponentsManager()->addEC(infiniteAmmo);

        if (!_data["time"].isDouble())
            throw std::exception("InfiniteAmmo: time is not a double");
        infiniteAmmo->setDuration(_data["time"].asDouble());

        if (!_data["timeEffect"].isDouble())
            throw std::exception("InfiniteAmmo: timeEffect is not a double");
        infiniteAmmo->setTimeEffect(_data["timeEffect"].asDouble());
        infiniteAmmo->setActive(true);

        return infiniteAmmo;
    };
};

REGISTER_FACTORY("InfiniteAmmo", InfiniteAmmoEC);
