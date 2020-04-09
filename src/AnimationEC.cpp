#include "AnimationEC.h"
#include "ComponentsManager.h"
#include "Entity.h"
#include "FactoriesFactory.h"
#include "Scene.h"
#include "TridimensionalObjectRC.h"

#include <OgreAnimationState.h>
#include <OgreEntity.h>
#include <OgreFrameListener.h>
#include <json.h>

void AnimationEC::checkEvent(const Ogre::FrameEvent& evt) {
    if (currentAnim != "")
        animations.find(currentAnim)->second->addTime(evt.timeSinceLastFrame);
}

void AnimationEC::startAnimation(std::string name) {
    stopCurrentAnimation();

    currentAnim = name;
    animations.find(currentAnim)->second->setEnabled(true);
}

void AnimationEC::stopCurrentAnimation() {
    if (currentAnim != "") {
        animations.find(currentAnim)->second->setEnabled(false);
        currentAnim = "";
    }
}

void AnimationEC::addAnimation(std::string name, bool loop) {
    TridimensionalObjectRC* renderFather =
        reinterpret_cast<TridimensionalObjectRC*>(
            father->getComponent("TridimensionalObjectRC"));

    Ogre::AnimationState* newAnimation;
    newAnimation = renderFather->getOgreEntity()->getAnimationState(name);
    newAnimation->setEnabled(false);
    newAnimation->setLoop(loop);

    animations.emplace(name, newAnimation);
}

// FACTORY INFRASTRUCTURE
AnimationECFactory::AnimationECFactory() = default;

Component* AnimationECFactory::create(Entity* _father, Json::Value& _data,
                                      Scene* _scene) {
    AnimationEC* animations = new AnimationEC();
    _scene->getComponentsManager()->addEC(animations);

    animations->setFather(_father);
    animations->setScene(_scene);

    if (_data["animations"].isArray()) {
        if (!_data["animations"][0].isObject())
            throw std::exception(
                "AnimationEC: animations is not an array of objects. Every object must have this structure: \n {\nname: string\nloop: boolean\n}");

        Json::Value anim = _data["animations"];
        int size = anim.size();
        for (int i = 0; i < size; i++)
            if (!anim[i]["name"].isString() || !anim[i]["loop"].isBool())
                throw std::exception(
                    "AnimationEC: name is not a string or loop is not a boolean");
            else
                animations->addAnimation(anim[i]["name"].asString(),
                                         anim[i]["loop"].asBool());

    }

    return animations;
};

DEFINE_FACTORY(AnimationEC);
