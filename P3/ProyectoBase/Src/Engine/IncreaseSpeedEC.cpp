#include "IncreaseSpeedEC.h"

#include "ComponentsManager.h"
#include "Entity.h"
#include "FactoriesFactory.h"
#include "Factory.h"
#include "OgreVector3.h"
#include "PlayerMovementIC.h"
#include "RigidbodyPC.h"
#include "Scene.h"
#include "TransformComponent.h"
#include "TridimensionalObjectRC.h"

#include <iostream>
#include <json.h>

IncreaseSpeedEC::IncreaseSpeedEC() {}

IncreaseSpeedEC::~IncreaseSpeedEC() {
    setActive(false);
    scene->getComponentsManager()->eraseEC(this);
}

void IncreaseSpeedEC::checkEvent() {
    PowerUpEC::checkEvent();

    if (!picked && getCollisionWithPlayer()) {
        picked = true;
        PlayerMovementIC* playerMovement = dynamic_cast<PlayerMovementIC*>(
            scene->getEntitybyId("Player")->getComponent("PlayerMovementIC"));

        originalSpeed = playerMovement->getMovementSpeed();
        playerMovement->setMovementSpeed(originalSpeed * (1 + speedIncrement));

        // TODO: Delete the entire object
        scene->getComponentsManager()->eraseRC(
            (dynamic_cast<TridimensionalObjectRC*>(
                father->getComponent("TridimensionalObjectRC"))));
        scene->getComponentsManager()->erasePC(
            (dynamic_cast<RigidbodyPC*>(father->getComponent("RigidbodyPC"))));
        scene->getComponentsManager()->eraseDC(
            (dynamic_cast<TransformComponent*>(
                father->getComponent("TransformComponent"))));
    }
    if (!picked) { // delete item when the effect has passed
        if (timeDisappear()) {
            scene->getComponentsManager()->eraseEC(this);

            scene->getComponentsManager()->eraseRC(
                (dynamic_cast<TridimensionalObjectRC*>(
                    father->getComponent("TridimensionalObjectRC"))));
            scene->getComponentsManager()->erasePC((dynamic_cast<RigidbodyPC*>(
                father->getComponent("RigidbodyPC"))));
            scene->getComponentsManager()->eraseDC(
                (dynamic_cast<TransformComponent*>(
                    father->getComponent("TransformComponent"))));
        }
    } else if (picked && timeDisappearEffect()) { // delete item when the effect has
                                        // passed
        PlayerMovementIC* playerMovement = dynamic_cast<PlayerMovementIC*>(
            scene->getEntitybyId("Player")->getComponent("PlayerMovementIC"));

        playerMovement->setMovementSpeed(originalSpeed);

        scene->getComponentsManager()->eraseEC(this);
        // TODO: Delete the entire object
    }
}

bool IncreaseSpeedEC::timeDisappearEffect() {
    float seconds = clock() / static_cast<float>(CLOCKS_PER_SEC);

    if (!startPicked) {
        time = seconds;
        startPicked = true;
    }
    if (time + timeEffect <= seconds) {
        return true;
    }

    return false;
}

void IncreaseSpeedEC::setTimeEffect(float _timeEffect) {
    timeEffect = _timeEffect;
}

void IncreaseSpeedEC::setSpeedIncrement(float _speedIncrement) {
    speedIncrement = _speedIncrement;
}

// FACTORY INFRASTRUCTURE
class IncreaseSpeedECFactory final : public ComponentFactory {
  public:
    IncreaseSpeedECFactory() = default;

    Component* create(Entity* _father, Json::Value& _data, Scene* scene) {
        IncreaseSpeedEC* increaseSpeedIC = new IncreaseSpeedEC();
        scene->getComponentsManager()->addEC(increaseSpeedIC);
        increaseSpeedIC->setFather(_father);
        increaseSpeedIC->setScene(scene);

        if (!_data["time"].isDouble())
            throw std::exception("IncreaseSpeed: time is not a double");
        increaseSpeedIC->setDuration(_data["time"].asDouble());
        if (!_data["timeEffect"].isDouble())
            throw std::exception("IncreaseSpeed: timeEffect is not a double");
        increaseSpeedIC->setTimeEffect(_data["timeEffect"].asDouble());
        if (!_data["speedIncrement"].isDouble())
            throw std::exception(
                "IncreaseSpeed: speedIncrement is not a double");
        increaseSpeedIC->setSpeedIncrement(_data["speedIncrement"].asDouble());

        increaseSpeedIC->setActive(true);

        return increaseSpeedIC;
    }
};

REGISTER_FACTORY("IncreaseSpeedEC", IncreaseSpeedEC);
