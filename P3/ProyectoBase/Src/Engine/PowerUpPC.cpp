#include "PowerUpPC.h"
#include "ComponentsManager.h"
#include "FactoriesFactory.h"
#include "Factory.h"
#include "OgreRoot.h"
#include "RigidbodyPC.h"
#include "Scene.h"
#include "TransformComponent.h"
#include <Entity.h>
#include <json.h>

PowerUpPC::PowerUpPC() : picked(false), start(false) {}

PowerUpPC::~PowerUpPC() {}

void PowerUpPC::checkEvent() {

    if (!picked) {
        RigidbodyPC* rb =
            dynamic_cast<RigidbodyPC*>(father->getComponent("RigidbodyPC"));

        // check collision with player
        collisionWithPlayer = rb->collidesWith("Player");
    }

}
void PowerUpPC::setDuration(float _duration) {
    durationTotal = _duration;
    time = 0;
}

bool PowerUpPC::getCollisionWithPlayer() { return collisionWithPlayer; }

bool PowerUpPC::timeDisappear() {

    float seconds = clock() / static_cast<float>(CLOCKS_PER_SEC);

    if (!start) {
        time = seconds;
        start = true;
    }
    if (time + durationTotal <= seconds) {
        return true;
    }

    return false;
}
