#include "MedkitEC.h"

#include "ComponentsManager.h"
#include "Entity.h"
#include "FactoriesFactory.h"
#include "Factory.h"
#include "LifeC.h"
#include "OgreVector3.h"
#include "Scene.h"
#include "TransformComponent.h"

#include <iostream>
#include <json.h>

void MedkitEC::update() {
    PowerUpEC::update();
}

void MedkitEC::onPickUp() {
    if (!isPicked()) {
        setPicked(true);
        LifeC* playerHealth = dynamic_cast<LifeC*>(
            scene->getEntitybyId("Player")->getComponent("LifeC"));
        playerHealth->heal(playerHealth->getTotalLife());
    }
}

// FACTORY INFRASTRUCTURE
class MedkitECFactory final : public ComponentFactory {
  public:
    MedkitECFactory() = default;

    Component* create(Entity* _father, Json::Value& _data,
                      Scene* scene) override {
        MedkitEC* medkitEC = new MedkitEC();

        medkitEC->setFather(_father);
        medkitEC->setScene(scene);

        if (!_data["time"].isDouble())
            throw std::exception("Shield: time is not a double");
        medkitEC->setTimeBeforeDelete(_data["time"].asDouble());
        if (!_data["timeEffect"].isDouble())
            throw std::exception("Shield: timeEffect is not a double");
        medkitEC->setTimeOfEffect(_data["timeEffect"].asDouble());

        medkitEC->setActive(true);

        return medkitEC;
    };
};

REGISTER_FACTORY("medkitEC", MedkitEC);
