#include "ChangeGravityIC.h"
#include "ComponentsManager.h"
#include "Entity.h"
#include "FactoriesFactory.h"
#include "Scene.h"
#include "AnimationLC.h"

#include "OgreRoot.h"

#include <json.h>

#include <iostream>

ChangeGravityIC::ChangeGravityIC() {}

ChangeGravityIC::~ChangeGravityIC() {}

void ChangeGravityIC::handleInput(const SDL_Event& _event) {
    if (_event.type == SDL_KEYDOWN && _event.key.keysym.sym == SDLK_SPACE) {
        dynamic_cast<AnimationLC*>(father->getComponent("AnimationLC"))
            ->stopAnimations();
        dynamic_cast<AnimationLC*>(father->getComponent("AnimationLC"))
            ->startAnimation("Dance");
    }
    else if (dynamic_cast<AnimationLC*>(father->getComponent("AnimationLC"))
            ->animationFinished("Dance")) {
        dynamic_cast<AnimationLC*>(father->getComponent("AnimationLC"))
            ->startAnimation("RunTop");
        std::cout << "terminado" << '\n';
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

    return changeGravity;
};

DEFINE_FACTORY(ChangeGravityIC);