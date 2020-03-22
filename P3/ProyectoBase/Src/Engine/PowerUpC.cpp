#include "PowerUpC.h"

#include "ComponentsManager.h"
#include "FactoriesFactory.h"
#include "OgreVector3.h"
#include "Scene.h"
#include "TransformComponent.h"

#include "Factory.h"
#include <json.h>

void PowerUpC::checkEvent() {
    // if (collision(player))
    if (true) {
        switch (type) {
        case 1: // MEDKIT POWER UP
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            break;
        default:
            break;
        }
    }
}

void PowerUpC::update() {}

bool PowerUpC::isCollisionWithPlayer() { return false; }

void PowerUpC::setProbability(float _probability) {
    probability = _probability;
}

void PowerUpC::setDuration(float _duration) { duration = _duration; }

void PowerUpC::setType(int _type) { type = _type; }

void PowerUpC::isInstantaneous(bool _instantaneous) {
    instantaneous = _instantaneous;
}

// FACTORY INFRASTRUCTURE
class PowerUpCFactory final : public ComponentFactory {
  public:
    PowerUpCFactory() = default;
    Component* create(Entity* _father, Json::Value& _data,
                      Scene* scene) override {
        PowerUpC* powerUpC = new PowerUpC();

        powerUpC->setType(_data["powerUpC"].asInt());
        powerUpC->setProbability(_data["powerUpC"].asFloat());
        powerUpC->isInstantaneous(_data["powerUpC"].asBool());
        powerUpC->setDuration(_data["powerUpC"].asFloat());

        powerUpC->setFather(_father);
        scene->getComponentsManager()->addEC(powerUpC);

		return powerUpC;
    }
};

REGISTER_FACTORY("PowerUpC", PowerUpC)
