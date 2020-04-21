#pragma once
#include "Component.h"

namespace Ogre {
    struct FrameEvent;
}

// Abstract subcomponent from which every input component should inherit

class ListenerComponent : public Component {
  public:
    // Destroys the ListenerComponent, setting itself as inactive and
    // removing itself from the scene.
    virtual void destroy();

    // called by Ogre after all render targets have had their rendering commands
    // issued, but before render windows have been asked to flip their buffers
    // over.
    virtual void frameRendered(const Ogre::FrameEvent& evt) = 0;
};
