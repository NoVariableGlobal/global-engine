#include "AutomaticRiflePowerUpC.h"
#include "ComponentsManager.h"
#include "Entity.h"
#include "FactoriesFactory.h"
#include "Factory.h"
#include "HandGunC.h"
#include "Scene.h"
#include "WeaponControllerIC.h"

#include <iostream>

void AutomaticRiflePowerUpC::destroy() {
    scene->getComponentsManager()->eraseDC(this);
}

void AutomaticRiflePowerUpC::onPickUp() {
    dynamic_cast<WeaponControllerIC*>(
        scene->getEntitybyId("Player")->getComponent("WeaponControllerIC"))
        ->pickUpGun("AutomaticRifleC");
}

// FACTORY INFRASTRUCTURE
class AutomaticRiflePowerUpCFactory final : public ComponentFactory {
  public:
    AutomaticRiflePowerUpCFactory() = default;

    Component* create(Entity* _father, Json::Value& _data,
                      Scene* _scene) override {

        AutomaticRiflePowerUpC* automaticriflePowerUpC =
            new AutomaticRiflePowerUpC();

        _scene->getComponentsManager()->addDC(automaticriflePowerUpC);
        automaticriflePowerUpC->setFather(_father);
        automaticriflePowerUpC->setScene(_scene);

        return automaticriflePowerUpC;
    };
};

REGISTER_FACTORY("AutomaticRiflePowerUpC", AutomaticRiflePowerUpC);

