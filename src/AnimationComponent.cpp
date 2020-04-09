#include "AnimationComponent.h"
#include "ComponentsManager.h"
#include "Entity.h"
#include "FactoriesFactory.h"
#include "Scene.h"
#include "TridimensionalObjectRC.h"

#include <OgreAnimationState.h>
#include <OgreEntity.h>
#include <json.h>

void AnimationComponent::destroy() {
    setActive(false);
    scene->getComponentsManager()->eraseAC(this);
}

void AnimationComponent::frameRendered(const Ogre::FrameEvent& evt) {
    for (auto anim : animations)
        if (anim.second->getEnabled())
            anim.second->addTime(evt.timeSinceLastFrame);
}

void AnimationComponent::startAnimation(std::string name) {
    animations.find(name)->second->setEnabled(true);
}

void AnimationComponent::stopAnimations() {
    for (auto anim : animations)
        if (anim.second->getEnabled())
            anim.second->setEnabled(false);
}

void AnimationComponent::stopAnimation(std::string name) {
    animations.find(name)->second->setEnabled(false);
}

void AnimationComponent::addAnimation(std::string name, bool loop) {
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
AnimationComponentFactory::AnimationComponentFactory() = default;

Component* AnimationComponentFactory::create(Entity* _father,
                                             Json::Value& _data,
                                      Scene* _scene) {
    AnimationComponent* animations = new AnimationComponent();
    _scene->getComponentsManager()->addAC(animations);

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

DEFINE_FACTORY(AnimationComponent);
