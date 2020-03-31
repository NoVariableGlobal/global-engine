#include "IncreaseSpeedEC.h"
#include "ComponentsManager.h"
#include "Entity.h"
#include "FactoriesFactory.h"
#include "PlayerMovementIC.h"
#include "Scene.h"
#include <json.h>

void IncreaseSpeedEC::setEffect(bool value) {
    Entity* player = scene->getEntitybyId("Player");
    auto movement = reinterpret_cast<PlayerMovementIC*>(
        player->getComponent("PlayerMovementIC"));

    if (value) {
        originalSpeed_ = movement->getMovementSpeed();
        movement->setMovementSpeed(originalSpeed_ * (1 + speedIncrement_));
    } else {
        movement->setMovementSpeed(originalSpeed_);
    }
}

std::string IncreaseSpeedEC::getName() { return "IncreaseSpeedEC"; }

void IncreaseSpeedEC::setSpeedIncrement(double value) {
    speedIncrement_ = value;
}

// FACTORY INFRASTRUCTURE
IncreaseSpeedECFactory::IncreaseSpeedECFactory() = default;

    Component* IncreaseSpeedECFactory::create(Entity* _father, Json::Value& _data,
                                        Scene* scene) {
        IncreaseSpeedEC* increaseSpeedIC = new IncreaseSpeedEC();
        scene->getComponentsManager()->addEC(increaseSpeedIC);
        increaseSpeedIC->setFather(_father);
        increaseSpeedIC->setScene(scene);

        if (!_data["time"].isDouble())
            throw std::exception("IncreaseSpeed: time is not a double");
        increaseSpeedIC->setDuration(_data["time"].asDouble());
        if (!_data["timeEffect"].isDouble())
            throw std::exception("IncreaseSpeed: timeEffect is not a double");
        increaseSpeedIC->setDuration(_data["timeEffect"].asDouble());
        if (!_data["speedIncrement"].isDouble())
            throw std::exception(
                "IncreaseSpeed: speedIncrement is not a double");
        increaseSpeedIC->setSpeedIncrement(_data["speedIncrement"].asDouble());

        increaseSpeedIC->setActive(true);

        return increaseSpeedIC;
    }

DEFINE_FACTORY(IncreaseSpeedEC);
