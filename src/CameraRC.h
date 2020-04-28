#pragma once
#include "Factory.h"
#include "RenderComponent.h"
#include <string>

// FACTORY INFRASTRUCTURE DECLARATION
DECLARE_FACTORY(CameraRC);

namespace Ogre {
    class Camera;
    class SceneNode;
    class Viewport;
    class SceneManager;

    typedef float Real;
    template <int Dims, typename T> class Vector;
    typedef Vector<3, Real> Vector3;
} // namespace Ogre

class TransformComponent;

// TO DO: fix errors related to Ogre libraries and ApplicationContext
class CameraRC final : public RenderComponent {
    Ogre::SceneManager* msM_ = nullptr;
    Ogre::Camera* camera_ = nullptr;
    Ogre::Viewport* vp_ = nullptr;

    // camera offset relative to followed object
    Ogre::Vector3* cameraOffset_ = nullptr;
    Ogre::Vector3* look_ = nullptr;

    bool followX_ = false;
    bool followY_ = false;
    bool followZ_ = false;

    std::string target_ = "";

  public:
    CameraRC();
    ~CameraRC();

    // set camera
    void setCamera(const std::string& entityId);
    // get camera
    Ogre::Camera* getCamera() const;
    // set viewport
    void setViewport(Ogre::Vector3 colour);
    // set camera offset
    void setCameraOffset(Ogre::Vector3 offset);
    // set camera direction
    void lookAt(Ogre::Vector3 pos);
    // set target to follow
    void setTarget(std::string target);
    // set follow booleans
    void setFollow(Ogre::Vector3 follow);

    // called each frame
    virtual void render();
};
