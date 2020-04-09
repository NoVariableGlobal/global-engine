#pragma once
#include "Component.h"
#include "Factory.h"

#include <vector>
#include <map>
#include <string>
#include <OgreFrameListener.h>

DECLARE_FACTORY(AnimationComponent)

class AnimationComponent : public Component {
  private:
    // name, animation
    std::map<std::string, Ogre::AnimationState*> animations;
    // name of the current animation
    std::string currentAnim = "";

  public:
    // Destroys the AnimationC, setting itself as inactive and
    // removing itself from the scene.
    virtual void destroy();

    virtual void frameRendered(const Ogre::FrameEvent& evt);

    // set as current animation the specify animation
    void startAnimation(std::string name);
    // stop the current animation
    void stopCurrentAnimation();
    // add an animation to the map of animations
    void addAnimation(std::string name, bool loop);
};
