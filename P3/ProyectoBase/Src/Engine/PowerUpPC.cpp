#include "PowerUpPC.h"
#include "ComponentsManager.h"
#include "FactoriesFactory.h"
#include "Factory.h"
#include "Scene.h"
#include <Entity.h>
#include <json.h>
#include "TransformComponent.h"
#include "OgreRoot.h"
#include "RigidbodyPC.h"

PowerUpPC::PowerUpPC(): disappear(false) {}

PowerUpPC::~PowerUpPC() {}

void
    PowerUpPC::update() {
    TransformComponent* transform = dynamic_cast<TransformComponent*>(
        father->getComponent("TransformComponent"));
    RigidbodyPC* rb =
        dynamic_cast<RigidbodyPC*>(father->getComponent("RigidbodyPC"));

    // check collision with player
    //collisionWithPlayer = rb->collidesWith("Player");

    /*float seconds = clock() / static_cast<float>(CLOCKS_PER_SEC);
    if (seconds - time >= durationTotal) {
        time = seconds;
    }*/
}

void PowerUpPC::setDuration(float _duration) { durationTotal = _duration;
    time = 0;
}

bool PowerUpPC::getCollisionWithPlayer() { return collisionWithPlayer; }
