#include "PersistentPowerUpEC.h"
#include "Entity.h"
#include "PowerUpTrackerC.h"
#include "RigidbodyPC.h"
#include "Scene.h"
#include "TransformComponent.h"
#include "TridimensionalObjectRC.h"
#include <time.h>

void PersistentPowerUpEC::onDestroy() {
    PowerUpEC::onDestroy();
    reinterpret_cast<PowerUpTrackerC*>(
        scene->getEntitybyId("Player")->getComponent("PowerUpTrackerC"))
        ->removePowerUp(getName());
}

void PersistentPowerUpEC::checkEvent() {
    PowerUpEC::checkEvent();

    if (!getPicked() && getCollisionWithPlayer()) {
        setPicked(true);

        Entity* player = scene->getEntitybyId("Player");
        auto tracker = reinterpret_cast<PowerUpTrackerC*>(
            player->getComponent("PowerUpTrackerC"));
        auto previous = dynamic_cast<PersistentPowerUpEC*>(
            tracker->findComponent(getName()));

        // If the player already has this powerup refresh it
        if (previous == nullptr) {
            setEffect(true);

            father->getComponent("TridimensionalObjectRC")->setActive(false);
            father->getComponent("RigidbodyPC")->setActive(false);
            father->getComponent("TransformComponent")->setActive(false);

            // Add this powerUp to the tracker
            reinterpret_cast<PowerUpTrackerC*>(
                scene->getEntitybyId("Player")->getComponent("PowerUpTrackerC"))
                ->addPowerUp(getName(), this);
        } else {
            previous->setTime(clock() / static_cast<float>(CLOCKS_PER_SEC));
            PowerUpEC::onDestroy();
        }
    } else if (timeDisappearEffect()) { // delete item when the effect has
                                        // passed
        if (getPicked()) {
            setEffect(false);
            onDestroy();
        } else {
            PowerUpEC::onDestroy();
        }
    }
}
