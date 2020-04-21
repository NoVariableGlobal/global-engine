#include "AnimationLC.h"
#include "ComponentsManager.h"
#include "Entity.h"
#include "FactoriesFactory.h"
#include "Scene.h"
#include "TridimensionalObjectRC.h"

#include <Ogre.h>
#include <OgreAnimationState.h>
#include <json.h>

void AnimationLC::frameRendered(const Ogre::FrameEvent& evt) {
    for (auto anim : animations_)
        if (anim.second->getEnabled()) {
            if (anim.second->hasEnded()) {
                anim.second->setEnabled(false);
            } else {
                anim.second->addTime(evt.timeSinceLastFrame);
            }
        }
}

void AnimationLC::startAnimation(const std::string& name) {
    Ogre::AnimationState* anim = animations_.find(name)->second;
    anim->setTimePosition(0.0);
    anim->setEnabled(true);
}

void AnimationLC::stopAnimations() {
    for (auto anim : animations_)
        if (anim.second->getEnabled()) {
            anim.second->setEnabled(false);
        }
}

void AnimationLC::stopAnimation(const std::string& name) {
    animations_.find(name)->second->setEnabled(false);
}

bool AnimationLC::animationFinished(const std::string& name) {
    return animations_.find(name)->second->hasEnded();
}

void AnimationLC::addAnimation(const std::string& name, const bool loop) {
    auto* renderFather = reinterpret_cast<TridimensionalObjectRC*>(
        father_->getComponent("TridimensionalObjectRC"));

    Ogre::AnimationState* newAnimation =
        renderFather->getOgreEntity()->getAnimationState(name);
    newAnimation->setEnabled(false);
    newAnimation->setLoop(loop);

    animations_.emplace(name, newAnimation);
}

// FACTORY INFRASTRUCTURE
AnimationLCFactory::AnimationLCFactory() = default;

Component* AnimationLCFactory::create(Entity* _father, Json::Value& _data,
                                      Scene* _scene) {
    auto* animations = new AnimationLC();
    _scene->getComponentsManager()->addLC(animations);

    animations->setFather(_father);
    animations->setScene(_scene);

    if (_data["animations"].isArray()) {
        if (!_data["animations"][0].isObject())
            throw std::exception(
                "AnimationEC: animations is not an array of objects. Every "
                "object must have this structure: \n {\nname: string\nloop: "
                "boolean\n}");

        Json::Value anim = _data["animations"];
        const int size = anim.size();
        for (int i = 0; i < size; i++) {
            if (!anim[i]["name"].isString() || !anim[i]["loop"].isBool())
                throw std::exception("AnimationEC: name is not a string or "
                                     "loop is not a boolean");
            animations->addAnimation(anim[i]["name"].asString(),
                                     anim[i]["loop"].asBool());
        }
    }

    return animations;
};

DEFINE_FACTORY(AnimationLC);
