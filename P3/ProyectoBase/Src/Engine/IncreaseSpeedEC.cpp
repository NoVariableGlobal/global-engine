#include "IncreaseSpeedEC.h"

#include "ComponentsManager.h"
#include "Entity.h"
#include "FactoriesFactory.h"
#include "Factory.h"
#include "PlayerMovementIC.h"
#include "OgreVector3.h"
#include "RigidbodyPC.h"
#include "Scene.h"
#include "TransformComponent.h"
#include "TridimensionalObjectRC.h"

#include <iostream>
#include <json.h>

IncreaseSpeedEC::IncreaseSpeedEC() {}

IncreaseSpeedEC::~IncreaseSpeedEC() {}

void IncreaseSpeedEC::checkEvent() {
    PowerUpEC::checkEvent();

    if (!picked && getCollisionWithPlayer()) {
        PlayerMovementIC* playerMovement = dynamic_cast<PlayerMovementIC*>(
            scene->getEntitybyId("Player")->getComponent("PlayerMovementIC"));
        playerMovement->setMovementSpeed(playerMovement->getMovementSpeed() +
                                         playerMovement->getMovementSpeed()*0.5);
        picked = true;

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
            // TODO: Delete the entire object
            scene->getComponentsManager()->eraseEC(this);

            /*RenderComponent* render = dynamic_cast<RenderComponent*>(
                scene->getEntitybyId("Shield0")->getComponent(
                    "TridimensionalObjectRC"));
            compManager->deleteRC(render);
            delete this;*/
        }
    }
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

		increaseSpeedIC->setActive(true);

		return increaseSpeedIC;
	}
};

REGISTER_FACTORY("IncreaseSpeedEC", IncreaseSpeedEC);
