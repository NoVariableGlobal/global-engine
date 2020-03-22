#include "ChangeGravityIC.h"
#include "ComponentsManager.h"
#include "Entity.h"
#include "FactoriesFactory.h"
#include "Factory.h"
#include "RigidbodyPC.h"
#include "Scene.h"

#include "OgreRoot.h"

#include <json.h>

#include <iostream>

ChangeGravityIC::ChangeGravityIC() {}

ChangeGravityIC::~ChangeGravityIC() {}

void ChangeGravityIC::handleInput(const SDL_Event& _event) {
    if (_event.type == SDL_KEYDOWN && _event.key.keysym.sym == SDLK_SPACE) {
        movingIzq = !movingIzq;
        dynamic_cast<RigidbodyPC*>(father->getComponent("RigidbodyPC"))
            ->setGravity(!movingIzq ? Ogre::Vector3(speed, 0.0f, 0.0f) : Ogre::Vector3(-speed, 0.0f, 0.0f));
    }
}

void ChangeGravityIC::setSpeed(float _speed) { speed = _speed; }

// FACTORY INFRASTRUCTURE
class ChangeGravityICFactory final : public ComponentFactory {
  public:
    ChangeGravityICFactory() = default;

    Component* create(Entity* _father, Json::Value& _data,
                      Scene* scene) override {
        ChangeGravityIC* changeGravity = new ChangeGravityIC();
        scene->getComponentsManager()->addIC(changeGravity);

        changeGravity->setFather(_father);
        changeGravity->setScene(scene);

        if (!_data["speed"].isDouble())
            throw std::exception("ChangeGravityIC: speed is not a double");

        changeGravity->setSpeed(_data["speed"].asDouble());

        return changeGravity;
    };
};

REGISTER_FACTORY("ChangeGravityIC", ChangeGravityIC);
