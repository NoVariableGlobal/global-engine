#include "ConstantMovementPC.h"

#include "Component.h"
#include "ComponentsManager.h"
#include "FactoriesFactory.h"
#include "Factory.h"
#include "OgreRoot.h"
#include "RigidbodyPC.h"
#include "Scene.h"
#include <Entity.h>
#include <SDL.h>

#include <iostream>
#include <json.h>

ConstantMovementPC::ConstantMovementPC() {}

ConstantMovementPC::~ConstantMovementPC() {}

void ConstantMovementPC::destroy() {
    setActive(false);
    scene->getComponentsManager()->erasePC(this);
}

void ConstantMovementPC::update() {
    RigidbodyPC* rb =
        dynamic_cast<RigidbodyPC*>(father->getComponent("RigidbodyPC"));

    Ogre::Vector3 velocity = Ogre::Vector3(0.0f, speed, 0.0f);

    rb->setLinearVelocity(velocity);
}

void ConstantMovementPC::setSpeed(float _speed) { speed = _speed; }

float ConstantMovementPC::getSpeed() { return speed; }

// FACTORY INFRASTRUCTURE
class ConstantMovementPCFactory final : public ComponentFactory {
  public:
    ConstantMovementPCFactory() = default;

    Component* create(Entity* _father, Json::Value& _data,
                      Scene* _scene) override {
        ConstantMovementPC* constantMovementPC = new ConstantMovementPC();
        _scene->getComponentsManager()->addPC(constantMovementPC);

        constantMovementPC->setFather(_father);
        constantMovementPC->setScene(_scene);

        if (!_data["speed"].asInt())
            throw std::exception("constantMovementPC: speed is not an int");
        constantMovementPC->setSpeed(_data["speed"].asFloat());

        return constantMovementPC;
    };
};

REGISTER_FACTORY("ConstantMovementPC", ConstantMovementPC);
