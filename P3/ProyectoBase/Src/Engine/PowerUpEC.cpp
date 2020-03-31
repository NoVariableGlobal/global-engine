#include "PowerUpEC.h"
#include "ComponentsManager.h"
#include "Entity.h"
#include "OgreRoot.h"
#include "RigidbodyPC.h"
#include "Scene.h"
#include "TransformComponent.h"
#include <json.h>

PowerUpEC::PowerUpEC() = default;
PowerUpEC::~PowerUpEC() = default;

void PowerUpEC::checkEvent() {
    if (!picked_) {
        auto rb =
            reinterpret_cast<RigidbodyPC*>(father->getComponent("RigidbodyPC"));

        // check collision with player
        collisionWithPlayer_ = rb->collidesWith("Player");
    }
}

void PowerUpEC::setPicked(bool picked) { picked_ = picked; }

void PowerUpEC::setTime(float time) { time_ = time; }

void PowerUpEC::setDuration(float duration) {
    durationTotal_ = duration;
    time_ = 0;
}

void PowerUpEC::resetTime() {
    time_ = clock() / static_cast<float>(CLOCKS_PER_SEC);
}

bool PowerUpEC::getPicked() { return picked_; }

float PowerUpEC::getTime() { return time_; }

bool PowerUpEC::getCollisionWithPlayer() { return collisionWithPlayer_; }

bool PowerUpEC::timeDisappearEffect() {
    float seconds = clock() / static_cast<float>(CLOCKS_PER_SEC);

    if (!start_) {
        time_ = seconds;
        start_ = true;
    }

    if (time_ + durationTotal_ <= seconds) {
        return true;
    }

    return false;
}

void PowerUpEC::onDestroy() { scene->deleteEntity(father); }
