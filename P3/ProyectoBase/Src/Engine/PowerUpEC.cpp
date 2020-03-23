#include "PowerUpEC.h"

#include "ComponentsManager.h"
#include "FactoriesFactory.h"
#include "Factory.h"
#include "OgreRoot.h"
#include "RigidbodyPC.h"
#include "Scene.h"
#include "TransformComponent.h"
#include <Entity.h>
#include <json.h>

PowerUpEC::PowerUpEC() {}

PowerUpEC::~PowerUpEC() {}

void PowerUpEC::update() {
    TransformComponent* transform = dynamic_cast<TransformComponent*>(
        father->getComponent("TransformComponent"));
    RigidbodyPC* rb =
        dynamic_cast<RigidbodyPC*>(father->getComponent("RigidbodyPC"));

    // Checks collision with player
    collisionWithPlayer = rb->collidesWith("Player");

    // Works until timer is up
    float seconds = clock() / static_cast<float>(CLOCKS_PER_SEC);
    if (seconds - time >= durationTotal) {
        time = seconds;
        disappear = true;
    }
}

void PowerUpEC::setDuration(float _duration) {
    durationTotal = _duration;
    time = 0;
}

bool PowerUpEC::getCollisionWithPlayer() { return collisionWithPlayer; }
