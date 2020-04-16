#pragma once
#include "Factory.h"
#include "ListenerComponent.h"

#include <map>
#include <string>
#include <vector>

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
    // return true if the animation has finished and is enabled
    bool animationFinished(std::string name);
    // add an animation to the map of animations
    void addAnimation(std::string name, bool loop);
};
