#pragma once
#include "EventComponent.h"
#include "TransformComponent.h"

// FACTORY INFRASTRUCTURE DECLARATION
DECLARE_FACTORY(SoundListenerComponent);

class SoundListenerComponent : public EventComponent {

    TransformComponent* transform_ = nullptr;

  public:
    virtual void checkEvent(const Ogre::FrameEvent& evt);
};
