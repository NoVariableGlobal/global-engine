#include "PlayerMovementIC.h"
#include "Component.h"
#include "ComponentsManager.h"
#include "FactoriesFactory.h"
#include "Factory.h"
#include "OgreRoot.h"
#include "Scene.h"
#include "RigidbodyPC.h"
#include <Entity.h>
#include <SDL.h>
#include <iostream>
#include <json.h>

PlayerMovementIC::PlayerMovementIC() {}

PlayerMovementIC::~PlayerMovementIC() {}

void PlayerMovementIC::handleInput(const SDL_Event& _event) {
    RigidbodyPC* body = dynamic_cast<RigidbodyPC*>(father->getComponent("RigidbodyPC"));

    if (_event.type == SDL_KEYDOWN) {
        switch (_event.key.keysym.sym) {
        case SDLK_w:
            wDown = true;
            break;

        case SDLK_s:
            sDown = true;
            break;

        case SDLK_a:
            aDown = true;
            break;

        case SDLK_d:
            dDown = true;
            break;

        default:
            break;
        }
    } else if (_event.type == SDL_KEYUP) {
        switch (_event.key.keysym.sym) {
        case SDLK_w:
            wDown = false;
            break;

        case SDLK_s:
            sDown = false;
            break;

        case SDLK_a:
            aDown = false;
            break;

        case SDLK_d:
            dDown = false;
            break;

        default:
            break;
        }
    }

    Ogre::Vector3 velocity = Ogre::Vector3(0.0f, 0.0f, 0.0f);

    if (wDown)
        velocity += Ogre::Vector3(0.0f, 0.0f, -_speed);
    if (sDown)
        velocity += Ogre::Vector3(0.0f, 0.0f, _speed);
    if (aDown)
        velocity += Ogre::Vector3(-_speed, 0.0f, 0.0f);
    if (dDown)
        velocity += Ogre::Vector3(_speed, 0.0f, 0.0f);

    body->setLinearVelocity(velocity);
}

void PlayerMovementIC::setMovementSpeed(float speed) { _speed = speed; }

// FACTORY INFRASTRUCTURE
class PlayerMovementICFactory final : public ComponentFactory {
  public:
    PlayerMovementICFactory() = default;

    Component* create(Entity* _father, Json::Value& _data,
                      Scene* _scene) override {
        PlayerMovementIC* playerMovement = new PlayerMovementIC();
        _scene->getComponentsManager()->addIC(playerMovement);

        playerMovement->setFather(_father);
        playerMovement->setScene(_scene);

        if (!_data["speed"].asInt())
            throw std::exception("PlayerMovementIC: speed is not an int");
        playerMovement->setMovementSpeed(_data["speed"].asFloat());

        return playerMovement;
    };
};

REGISTER_FACTORY("PlayerMovementIC", PlayerMovementIC);
