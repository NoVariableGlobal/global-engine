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

MedkitEC::MedkitEC() : picked(false) {}

MedkitEC::~MedkitEC() {}

void MedkitEC::update() {
    PowerUpEC::update();
    if (getCollisionWithPlayer()) {
        LifeC* playerHealth = dynamic_cast<LifeC*>(
            scene->getEntitybyId("Player")->getComponent("LifeC"));
        playerHealth->heal(playerHealth->getTotalLife());
        currentDuration = timeEffect;
        picked = true;
    }
    if (picked && currentDuration <= 0) {
        ComponentsManager* compManager =
            dynamic_cast<ComponentsManager*>(scene->getComponentsManager());
        compManager->deleteEC(this);
    }
}

void MedkitEC::checkEvent() {}

void MedkitEC::setProbability(float _probability) {
    probability = _probability;
}

void MedkitEC::setTime(float _time) { time = _time; }

void MedkitEC::setTimeEffect(float _timeEffect) { timeEffect = _timeEffect; }

void MedkitEC::onCollisionActivate() {
    if (checkCollision()) {
        // player.setTotalLife(player.life);
        std::cout << "Health restored to full\n";
    }
    delete this;
}

bool MedkitEC::checkCollision() {
    // if (checkCollision(player)) { return true; }
    return true;
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
        scene->getComponentsManager()->addEC(medkitEC);

        if (!_data["probality"].isDouble())
            throw std::exception("Shield: probality is not a double");
        medkitEC->setProbability(_data["probality"].asDouble());
        if (!_data["time"].isDouble())
            throw std::exception("Shield: time is not a double");
        medkitEC->setTime(_data["time"].asDouble());
        if (!_data["timeEffect"].isDouble())
            throw std::exception("Shield: timeEffect is not a double");
        medkitEC->setTimeEffect(_data["timeEffect"].asDouble());

        medkitEC->setActive(true);

        return medkitEC;
    };
};

REGISTER_FACTORY("medkitEC", MedkitEC);
