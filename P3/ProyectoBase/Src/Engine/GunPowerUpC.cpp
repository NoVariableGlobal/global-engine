#include "GunPowerUpC.h"
#include "ComponentsManager.h"
#include "Entity.h"
#include "FactoriesFactory.h"
#include "Factory.h"
#include "HandGunC.h"
#include "Scene.h"
#include "WeaponControllerIC.h"
#include <json.h>
#include <iostream>

void GunPowerUpC::destroy() { 
	setActive(false);
	scene->getComponentsManager()->eraseDC(this); 
}

void GunPowerUpC::onPickUp() {
    dynamic_cast<WeaponControllerIC*>(
        scene->getEntitybyId("Player")->getComponent("WeaponControllerIC"))
        ->pickUpGun(_gunId);
}

void GunPowerUpC::setGunId(const std::string& gunId) { _gunId = gunId; }

// FACTORY INFRASTRUCTURE
class GunPowerUpCFactory final : public ComponentFactory {
  public:
    GunPowerUpCFactory() = default;


    Component* create(Entity* _father, Json::Value& _data,
                      Scene* _scene) override {


        GunPowerUpC* gunPowerUpC = new GunPowerUpC();

        if (!_data["gunId"].isString())
            throw std::exception("GunPowerUpC: gunId is not a string");
        gunPowerUpC->setGunId(_data["gunId"].asString());

        _scene->getComponentsManager()->addDC(gunPowerUpC);
        gunPowerUpC->setFather(_father);
        gunPowerUpC->setScene(_scene);

        return gunPowerUpC;
    };
};

REGISTER_FACTORY("GunPowerUpC", GunPowerUpC);