#include "PowerUpC.h"

#include "ComponentsManager.h"
#include "FactoriesFactory.h"
#include "OgreVector3.h"
#include "Scene.h"

#include "Factory.h"
#include <json.h>

void PowerUpC::onPickUp() {}

void PowerUpC::setProbability(float _probability) {
    probability = _probability;
}

void PowerUpC::setDuration(float _duration) { duration = _duration; }

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

        powerUpC->setProbability(_data["powerUpC"].asFloat());
        powerUpC->isInstantaneous(_data["powerUpC"].asBool());
        powerUpC->setDuration(_data["powerUpC"].asFloat());

        powerUpC->setFather(_father);
        //scene->getComponentsManager()->addPC(powerUpC);

		return powerUpC;
    }
};

REGISTER_FACTORY("PowerUpC", PowerUpC)
