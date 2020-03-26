#include "SemiAutomaticEC.h"
#include "ComponentsManager.h"
#include "Entity.h"
#include "FactoriesFactory.h"
#include "Factory.h"
#include "Scene.h"
#include "WeaponControllerIC.h"
#include <time.h>
#include <iostream>
#include <json.h>
#include "OgreRoot.h"
#include "Entity.h"
#include "GunC.h"

SemiAutomaticEC::SemiAutomaticEC() {}

SemiAutomaticEC::~SemiAutomaticEC() {}

void SemiAutomaticEC::destroy() {
    setActive(false);
    scene->getComponentsManager()->eraseEC(this);
}

void SemiAutomaticEC::checkEvent() {
    if (timeCadence()) {
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

// FACTORY INFRASTRUCTURE
class SpawnerECFactory final : public ComponentFactory {
  public:
    SpawnerECFactory() = default;

    Component* create(Entity* _father, Json::Value& _data,
                      Scene* scene) override {
        SemiAutomaticEC* semiAutomatic = new SemiAutomaticEC();

        semiAutomatic->setFather(_father);
        scene->getComponentsManager()->addEC(semiAutomatic);

		if (!_data["cadence"].isDouble())
            throw std::exception("Shield: time is not a double");
                semiAutomatic->setCadence(_data["cadence"].asDouble());

        semiAutomatic->setActive(true);

        return semiAutomatic;
    };
};

REGISTER_FACTORY("SemiAutomaticEC", SemiAutomaticEC);