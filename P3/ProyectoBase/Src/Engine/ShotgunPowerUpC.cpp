#include "ShotgunPowerUpC.h"
#include "ComponentsManager.h"
#include "Entity.h"
#include "FactoriesFactory.h"
#include "Factory.h"
#include "HandGunC.h"
#include "Scene.h"
#include "WeaponControllerIC.h"

#include <iostream>

void ShotgunPowerUpC::destroyMyself() { scene->getComponentsManager()->eraseDC(this); }

void ShotgunPowerUpC::onPickUp() {
    dynamic_cast<WeaponControllerIC*>(
        scene->getEntitybyId("Player")->getComponent("WeaponControllerIC"))
        ->pickUpGun("ShotgunC");
}

// FACTORY INFRASTRUCTURE
class ShotgunPowerUpCFactory final : public ComponentFactory {
  public:
    ShotgunPowerUpCFactory() = default;

    Component* create(Entity* _father, Json::Value& _data,
                      Scene* _scene) override {

        ShotgunPowerUpC* shotgunPowerUpC = new ShotgunPowerUpC();

        _scene->getComponentsManager()->addDC(shotgunPowerUpC);
        shotgunPowerUpC->setFather(_father);
        shotgunPowerUpC->setScene(_scene);

        return shotgunPowerUpC;
    };
};

REGISTER_FACTORY("ShotgunPowerUpC", ShotgunPowerUpC);