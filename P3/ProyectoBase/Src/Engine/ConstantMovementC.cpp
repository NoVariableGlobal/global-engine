#include "ConstantMovementC.h"

#include "Component.h"
#include "ComponentsManager.h"
#include "FactoriesFactory.h"
#include "Factory.h"
#include "OgreRoot.h"
#include "RigidbodyPC.h"
#include "Scene.h"
#include "Entity.h"

#include <json.h>

ConstantMovementC::ConstantMovementC() {}

ConstantMovementC::~ConstantMovementC() {}

void ConstantMovementC::destroy() {
    setActive(false);
    scene->getComponentsManager()->eraseDC(this);
}

void ConstantMovementC::setSpeed(float _speed) {
    speed = _speed;

    RigidbodyPC* body =
        dynamic_cast<RigidbodyPC*>(father->getComponent("RigidbodyPC"));

    body->setLinearVelocity(Ogre::Vector3(0.0f, speed, 0.0f));
}

float ConstantMovementC::getSpeed() { return speed; }

// FACTORY INFRASTRUCTURE
class ConstantMovementCFactory final : public ComponentFactory {
  public:
    ConstantMovementCFactory() = default;

    Component* create(Entity* _father, Json::Value& _data,
                      Scene* _scene) override {
        ConstantMovementC* constantMovementPC = new ConstantMovementC();
        _scene->getComponentsManager()->addDC(constantMovementPC);

        constantMovementPC->setFather(_father);
        constantMovementPC->setScene(_scene);

        if (!_data["speed"].asInt())
            throw std::exception("ConstantMovementC: speed is not an int");
        constantMovementPC->setSpeed(_data["speed"].asFloat());

        return constantMovementPC;
    };
};

REGISTER_FACTORY("ConstantMovementC", ConstantMovementC);