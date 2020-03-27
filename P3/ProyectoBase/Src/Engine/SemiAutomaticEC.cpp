#include "SemiAutomaticEC.h"
#include "ComponentsManager.h"
#include "Entity.h"
#include "FactoriesFactory.h"
#include "Factory.h"
#include "GunC.h"
#include "OgreRoot.h"
#include "Scene.h"
#include "WeaponControllerIC.h"
#include <iostream>
#include <json.h>
#include <time.h>

SemiAutomaticEC::SemiAutomaticEC() {}

SemiAutomaticEC::~SemiAutomaticEC() {}

void SemiAutomaticEC::destroy() {
    setActive(false);
    scene->getComponentsManager()->eraseEC(this);
}

void SemiAutomaticEC::checkEvent() {
    cadence = (dynamic_cast<WeaponControllerIC*>(
                   father->getComponent("WeaponControllerIC")))
                  ->getCurrentGun()
                  ->getcadence();
    if (shoot && timeCadence()) {
        (dynamic_cast<WeaponControllerIC*>(
             father->getComponent("WeaponControllerIC")))
            ->getCurrentGun()
            ->shoot();
    }
}

bool SemiAutomaticEC::timeCadence() {
    float seconds = clock() / static_cast<float>(CLOCKS_PER_SEC);

    if (seconds - lastTimecadence >= cadence) {
        lastTimecadence = seconds;
        return true;
    }

    return false;
}

void SemiAutomaticEC::setCadence(double _cadence) { cadence = _cadence; }

void SemiAutomaticEC::setShoot(bool _shoot) { shoot = _shoot; }

// FACTORY INFRASTRUCTURE
class SemiAutomaticECFactory final : public ComponentFactory {
  public:
    SemiAutomaticECFactory() = default;

    Component* create(Entity* _father, Json::Value& _data,
                      Scene* scene) override {
        SemiAutomaticEC* semiAutomatic = new SemiAutomaticEC();

        semiAutomatic->setFather(_father);
        scene->getComponentsManager()->addEC(semiAutomatic);

        semiAutomatic->setActive(true);

        return semiAutomatic;
    };
};

REGISTER_FACTORY("SemiAutomaticEC", SemiAutomaticEC);