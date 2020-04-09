#pragma once
#include "EventComponent.h"
#include "Factory.h"

#include <vector>
#include <map>
#include <string>

DECLARE_FACTORY(AnimationEC);

namespace Ogre {
    class AnimationState;
}

class AnimationEC : public EventComponent {
  private:
    // name, animation
    std::map<std::string, Ogre::AnimationState*> animations;
    // name of the current animation
    std::string currentAnim = "";

  public:
    virtual void checkEvent(const Ogre::FrameEvent& evt);

    // set as current animation the specify animation
    void startAnimation(std::string name);
    // stop the current animation
    void stopCurrentAnimation();
    // add an animation to the map of animations
    void addAnimation(std::string name, bool loop);
};
