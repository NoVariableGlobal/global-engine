#include "IncreaseSpeedEC.h"

#include "ComponentsManager.h"
#include "Entity.h"
#include "FactoriesFactory.h"
#include "Factory.h"
#include "OgreVector3.h"
#include "PlayerMovementIC.h"
#include "PowerUpTrackerC.h"
#include "RigidbodyPC.h"
#include "Scene.h"
#include "TransformComponent.h"
#include "TridimensionalObjectRC.h"

#include <iostream>
#include <json.h>

IncreaseSpeedEC::IncreaseSpeedEC() {}

IncreaseSpeedEC::~IncreaseSpeedEC() {}

void IncreaseSpeedEC::destroy() {
    setActive(false);
    scene->getComponentsManager()->eraseEC(this);
}

void IncreaseSpeedEC::checkEvent() {
    PowerUpEC::checkEvent();

    // Check if the player is colliding with this
    if (!picked && getCollisionWithPlayer()) {
        picked = true;

        PowerUpTrackerC* tracker = dynamic_cast<PowerUpTrackerC*>(
            scene->getEntitybyId("Player")->getComponent("PowerUpTrackerC"));
        IncreaseSpeedEC* incSpeed = dynamic_cast<IncreaseSpeedEC*>(
            tracker->getComponent("IncreaseSpeedEC"));

        // If the player already has this powerup refresh it
        if (incSpeed != nullptr) {
            incSpeed->setPickedTime(clock() /
                                    static_cast<float>(CLOCKS_PER_SEC));
            scene->deleteEntity(father);
        } else {
            PlayerMovementIC* playerMovement = dynamic_cast<PlayerMovementIC*>(
                scene->getEntitybyId("Player")->getComponent(
                    "PlayerMovementIC"));
            originalSpeed = playerMovement->getMovementSpeed();
            playerMovement->setMovementSpeed(originalSpeed *
                                             (1 + speedIncrement));

            dynamic_cast<TridimensionalObjectRC*>(
                father->getComponent("TridimensionalObjectRC"))
                ->setActive(false);

            dynamic_cast<RigidbodyPC*>(father->getComponent("RigidbodyPC"))
                ->setActive(false);

            dynamic_cast<TransformComponent*>(
                father->getComponent("TransformComponent"))
                ->setActive(false);

            // Add this powerUp to the tracker
            dynamic_cast<PowerUpTrackerC*>(
                scene->getEntitybyId("Player")->getComponent("PowerUpTrackerC"))
                ->addPowerUp("IncreaseSpeedEC", this);
        }
    }

    // delete item when the time has passed and the player has not picked it
    if (!picked) {
        if (timeDisappear()) {
            dynamic_cast<PowerUpTrackerC*>(
                scene->getEntitybyId("Player")->getComponent("PowerUpTrackerC"))
                ->removePowerUp("IncreaseSpeedEC");
            scene->deleteEntity(father);
        }
        // delete item when the effect has passed
    } else if (picked && timeDisappearEffect()) {
        PlayerMovementIC* playerMovement = dynamic_cast<PlayerMovementIC*>(
            scene->getEntitybyId("Player")->getComponent("PlayerMovementIC"));
        playerMovement->setMovementSpeed(originalSpeed);

        dynamic_cast<PowerUpTrackerC*>(
            scene->getEntitybyId("Player")->getComponent("PowerUpTrackerC"))
            ->removePowerUp("IncreaseSpeedEC");
        scene->deleteEntity(father);
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

void IncreaseSpeedEC::setPickedTime(float _time) { time = _time; }

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
