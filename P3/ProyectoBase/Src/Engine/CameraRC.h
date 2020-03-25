#pragma once

#include "RenderComponent.h"

#include <string>

namespace Ogre {
    class Camera;
    class SceneNode;
    class Viewport;
    class SceneManager;

    typedef float Real;
    template <int dims, typename T> class Vector;
    typedef Vector<3, Real> Vector3;
} // namespace Ogre

class TransformComponent;

// TO DO: fix errors related to Ogre libraries and ApplicationContext
class CameraRC : public RenderComponent {
  private:
    Ogre::SceneManager* _msM = nullptr;
    Ogre::Camera* camera = nullptr;
    Ogre::Viewport* vp = nullptr;

    // camera offset relative to followed object
    Ogre::Vector3* cameraOffset = nullptr;
    Ogre::Vector3* look = nullptr;

    bool followX = false,
        followY = false,
        followZ = false;

    std::string target = "";

  public:
    CameraRC();
    ~CameraRC();

    virtual void destroy();
    // set camera
    void setCamera(std::string _entityID);
    // get camera
    Ogre::Camera* getCamera();
    // set viewport
    void setViewport(Ogre::Vector3 _colour);
    // set camera offset
    void setCameraOffset(Ogre::Vector3(_offset));
    // set camera direction
    void lookAt(Ogre::Vector3 _pos);
    // set target to follow
    void setTarget(std::string _target);
    // set follow booleans
    void setFollow(Ogre::Vector3 _follow);

    // called each frame
    virtual void render();
};
