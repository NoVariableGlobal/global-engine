#pragma once


#include "SoundListenerComponent.h"
#include "SoundContext.h"
#include "Entity.h"
#include "FactoriesFactory.h"

void SoundListenerComponent::checkEvent() {
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
    SoundListenerComponent* soundListenerComponent = new SoundListenerComponent();

    soundListenerComponent->setFather(_father);
    soundListenerComponent->setScene(_scene);

    return soundListenerComponent;

}

DEFINE_FACTORY(SoundListenerComponent);