#pragma once
#include "Factory.h"
#include "ListenerComponent.h"

#include <map>
#include <string>

namespace Ogre {
    class AnimationState;
}

DECLARE_FACTORY(AnimationLC)

class AnimationLC final : public ListenerComponent {
    // name, animation
    std::map<std::string, Ogre::AnimationState*> animations_;

  public:
    void frameRendered(const Ogre::FrameEvent& evt) override;

    // active the specify animation
    void startAnimation(std::string name);
    // stop all the enabled animations
    void stopAnimations();
    // stop the animation specified
    void stopAnimation(std::string name);
    // return true if the animation is enabled
    bool animationFinished(std::string name);
    // add an animation to the map of animations
    void addAnimation(std::string name, bool loop);
};
