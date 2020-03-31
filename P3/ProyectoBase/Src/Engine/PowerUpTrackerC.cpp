#include "PowerUpTrackerC.h"
#include "ComponentsManager.h"
#include "FactoriesFactory.h"
#include "Factory.h"
#include "Scene.h"
#include "Util.h"

void PowerUpTrackerC::destroy() {
    setActive(false);
    scene->getComponentsManager()->eraseDC(this);
}

Component* PowerUpTrackerC::findComponent(std::string name) {
    return try_find(powerUps, name);
}

void PowerUpTrackerC::addPowerUp(std::string name, Component* powerUp) {
    powerUps.insert({name, powerUp});
}

void PowerUpTrackerC::removePowerUp(std::string name) {
    auto it = powerUps.begin();
    while (it != powerUps.end()) {
        if (it->first == name) {
            powerUps.erase(it);
            break;
        }
    }
}

// FACTORY INFRASTRUCTURE
class PowerUpTrackerCFactory final : public ComponentFactory {
  public:
    PowerUpTrackerCFactory() = default;

    Component* create(Entity* _father, Json::Value& _data,
                      Scene* _scene) override {
        PowerUpTrackerC* powerUpTracker = new PowerUpTrackerC();
        _scene->getComponentsManager()->addDC(powerUpTracker);

        powerUpTracker->setFather(_father);
        powerUpTracker->setScene(_scene);

        return powerUpTracker;
    };
};

REGISTER_FACTORY("PowerUpTrackerC", PowerUpTrackerC);