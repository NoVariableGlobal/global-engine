#pragma once

#include "SoundListenerComponent.h"
#include "ComponentsManager.h"
#include "Entity.h"
#include "FactoriesFactory.h"
#include "Scene.h"
#include "SoundContext.h"

#include <OgreFrameListener.h>

void SoundListenerComponent::checkEvent(const Ogre::FrameEvent& evt) {
    if (transform_ == nullptr)
        transform_ = dynamic_cast<TransformComponent*>(
            father->findComponent("TransformComponent"));
    SoundContext::getInstance()->updatePosition(transform_->getPosition());
}

// FACTORY INFRASTRUCTURE DEFINITION

SoundListenerComponentFactory::SoundListenerComponentFactory() = default;

Component* SoundListenerComponentFactory::create(Entity* _father,
                                                 Json::Value& _data,
                                                 Scene* _scene) {
    SoundListenerComponent* soundListenerComponent =
        new SoundListenerComponent();

    soundListenerComponent->setFather(_father);
    soundListenerComponent->setScene(_scene);
    _scene->getComponentsManager()->addEC(soundListenerComponent);
    return soundListenerComponent;
}

DEFINE_FACTORY(SoundListenerComponent);