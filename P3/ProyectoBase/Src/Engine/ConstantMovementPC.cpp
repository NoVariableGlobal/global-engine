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
    if (counter >= timer) {
        counter = 0;
        speed += 10;
        std::cout << "\nspeed increased. Now it is: " << speed << "\n";
	}
    counter++;
}

void ConstantMovementPC::setSpeed(float _speed) { speed = _speed; }

void ConstantMovementPC::setTimer(float _timer) { timer = _timer; }

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
            throw std::exception("ConstantMovementPC: speed is not an int");
        constantMovementPC->setSpeed(_data["speed"].asFloat());

        if (!_data["timer"].asInt())
            throw std::exception("ConstantMovementPC: timer is not an int");
        constantMovementPC->setTimer(_data["timer"].asInt());

        return constantMovementPC;
    };
};

REGISTER_FACTORY("ConstantMovementPC", ConstantMovementPC);
