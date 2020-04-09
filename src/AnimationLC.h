#pragma once
#include "ListenerComponent.h"
#include "Factory.h"

#include <vector>
#include <map>
#include <string>

DECLARE_FACTORY(AnimationLC)

class AnimationLC : public ListenerComponent {
  private:
    // name, animation
    std::map<std::string, Ogre::AnimationState*> animations;

  public:
    virtual void frameRendered(const Ogre::FrameEvent& evt);

    // active the specify animation
    void startAnimation(std::string name);
    // stop all the enabled animations
    void stopAnimations();
    // stop the animation specified
    void stopAnimation(std::string name);
    // add an animation to the map of animations
    void addAnimation(std::string name, bool loop);
};
