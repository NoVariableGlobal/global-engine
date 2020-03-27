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

    if (gun_ != nullptr) {
        gun_->setInfiniteAmmo(false);
    }
}

void InfiniteAmmoEC::checkEvent() {
    PowerUpEC::checkEvent();

    if (!picked && getCollisionWithPlayer()) {
        auto weaponController = dynamic_cast<WeaponControllerIC*>(
            father->getComponent("WeaponControllerIC"));
        gun_ = weaponController->getCurrentGun();
        gun_->setInfiniteAmmo(true);
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

        infiniteAmmo->setActive(true);

        return infiniteAmmo;
    };
};

REGISTER_FACTORY("InfiniteAmmo", InfiniteAmmoEC);
