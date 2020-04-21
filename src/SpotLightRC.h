#pragma once

#include "Factory.h"
#include "RenderComponent.h"
#include <string>

// FACTORY INFRASTRUCTURE DECLARATION
DECLARE_FACTORY(SpotLightRC);

namespace Ogre {
    class SceneNode;
    class SceneManager;
    class Light;

    typedef float Real;
    template <int Dims, typename T> class Vector;
    typedef Vector<3, Real> Vector3;
} // namespace Ogre

class SpotLightRC final : public RenderComponent {
    Ogre::SceneManager* msM_ = nullptr;
    Ogre::Light* light_ = nullptr;

  public:
    SpotLightRC();
    virtual ~SpotLightRC();

    // set light
    void setLight(std::string entityId);
    // get light
    Ogre::Light* getLight() const;
    // set the colour of the light
    void setColour(Ogre::Vector3 colour);
    // set the direction of the light
    void setDirection(Ogre::Vector3 dir);

    // called each frame
    virtual void render();
};
