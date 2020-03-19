#include "PlayerMovementIC.h"
#include "Component.h"
#include "ComponentsManager.h"
#include "FactoriesFactory.h"
#include "Factory.h"
#include "OgreRoot.h"
#include "Scene.h"
#include "TransformComponent.h"
#include <Entity.h>
#include <SDL.h>
#include <iostream>
#include <json.h>

PlayerMovementIC::PlayerMovementIC() {}

PlayerMovementIC::~PlayerMovementIC() {}

void PlayerMovementIC::handleInput(const SDL_Event& _event) {
    TransformComponent* transform = dynamic_cast<TransformComponent*>(
        father->getComponent("TransformComponent"));

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

    if (wDown)
        transform->setPosition(transform->getPosition() +
                               Ogre::Vector3(0.0f, 0.0f, -_speed));
    if (sDown)
        transform->setPosition(transform->getPosition() +
                               Ogre::Vector3(0.0f, 0.0f, _speed));
    if (aDown)
        transform->setPosition(transform->getPosition() +
                               Ogre::Vector3(-_speed, 0.0f, 0.0f));
    if (dDown)
        transform->setPosition(transform->getPosition() +
                               Ogre::Vector3(_speed, 0.0f, 0.0f));
}

void PlayerMovementIC::setMovementSpeed(float speed) { _speed = speed; }

// FACTORY INFRASTRUCTURE
class PlayerMovementICFactory final : public ComponentFactory {
  public:
    PlayerMovementICFactory() = default;

    Component* create(Entity* _father, Json::Value& _data,
                      Scene* scene) override {
        PlayerMovementIC* playerMovement = new PlayerMovementIC();
        scene->getComponentsManager()->addIC(playerMovement);

        playerMovement->setFather(_father);
        playerMovement->setScene(scene);

        if (!_data["speed"].asInt())
            throw std::exception("PlayerMovementIC: speed is not an int");
        playerMovement->setMovementSpeed(_data["speed"].asFloat());

        return playerMovement;
    };
};

REGISTER_FACTORY("PlayerMovementIC", PlayerMovementIC);
