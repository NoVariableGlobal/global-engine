#include "ChangeGravityIC.h"
#include "ComponentsManager.h"
#include "Entity.h"
#include "FactoriesFactory.h"
#include "RigidbodyPC.h"
#include "Scene.h"
#include "TridimensionalObjectRC.h"

#include "OgreRoot.h"

#include <json.h>

#include <iostream>

ChangeGravityIC::ChangeGravityIC() {}

ChangeGravityIC::~ChangeGravityIC() {}

void ChangeGravityIC::destroy() {
    setActive(false);
    scene->getComponentsManager()->eraseIC(this);
}

void ChangeGravityIC::handleInput(const SDL_Event& _event) {
    if (_event.type == SDL_KEYDOWN && _event.key.keysym.sym == SDLK_SPACE) {
        movingIzq = !movingIzq;

        RigidbodyPC* body =
            dynamic_cast<RigidbodyPC*>(father->getComponent("RigidbodyPC"));

        body->setGravity(!movingIzq ? Ogre::Vector3(speed, 0.0f, 0.0f)
                                    : Ogre::Vector3(-speed, 0.0f, 0.0f));

        body->setLinearVelocity(Ogre::Vector3(0.0f, 0.0f, 0.0f));

        dynamic_cast<TridimensionalObjectRC*>(
            father->getComponent("TridimensionalObjectRC"))
            ->setMaterial(!movingIzq ? mRight : mLeft);
    }
}

void ChangeGravityIC::setSpeed(float _speed) { speed = _speed; }

void ChangeGravityIC::setMaterialLeft(std::string _mLeft) { mLeft = _mLeft; }

void ChangeGravityIC::setMaterialRight(std::string _mRight) {
    mRight = _mRight;
}

// FACTORY INFRASTRUCTURE

ChangeGravityICFactory::ChangeGravityICFactory() = default;

Component* ChangeGravityICFactory::create(Entity* _father, Json::Value& _data,
                                          Scene* scene) {
    ChangeGravityIC* changeGravity = new ChangeGravityIC();
    scene->getComponentsManager()->addIC(changeGravity);

    changeGravity->setFather(_father);
    changeGravity->setScene(scene);

    if (!_data["speed"].isDouble())
        throw std::exception("ChangeGravityIC: speed is not a double");

    changeGravity->setSpeed(_data["speed"].asDouble());

    if (!_data["materialL"].isString())
        throw std::exception("ChangeGravityIC: materialL is not a string");

    changeGravity->setMaterialLeft(_data["materialL"].asString());

    if (!_data["materialR"].isString())
        throw std::exception("ChangeGravityIC: materialR is not a string");

    changeGravity->setMaterialRight(_data["materialR"].asString());

    return changeGravity;
};

DEFINE_FACTORY(ChangeGravityIC);