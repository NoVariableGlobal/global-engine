#pragma once

#include "RenderComponent.h"

#include <string>

namespace Ogre {
    class SceneNode;
    class SceneManager;
    class Light;

    typedef float Real;
    template <int dims, typename T> class Vector;
    typedef Vector<3, Real> Vector3;
} // namespace Ogre

class SpotLightRC : public RenderComponent {
  private:
    Ogre::SceneManager* _msM = nullptr;
    Ogre::Light* light = nullptr;

  public:
    SpotLightRC();
    virtual ~SpotLightRC();

    // set light
    void setLight(std::string _entityID);
    // get light
    Ogre::Light* getLight();
    // set the colour of the light
    void setColour(Ogre::Vector3 _colour);
    // set the direction of the light
    void setDirection(Ogre::Vector3 _dir);

    // called each frame
    virtual void render();
};
