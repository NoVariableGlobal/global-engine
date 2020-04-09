#pragma once

#include "Component.h"
#include <OgreFrameListener.h>

// Abstract class for every component that has update but is not physic or input
class EventComponent : public Component {
  public:
    EventComponent();
    virtual ~EventComponent();
    virtual void checkEvent(const Ogre::FrameEvent& evt) = 0;

    // Destroys the EventComponent, setting itself as inactive and
    // removing itself from the scene.
    virtual void destroy();
};