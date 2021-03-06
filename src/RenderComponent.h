#pragma once
#include "Component.h"

// Abstract subcomponent from which every graphic component should inherit

namespace Ogre {
    class Entity;
    class SceneNode;
    typedef float Real;
    template <int Dims, typename T> class Vector;
    typedef Vector<3, Real> Vector3;
} // namespace Ogre

class RenderComponent : public Component {
  protected:
    // entity and scene node of the object this render component belongs to
    Ogre::Entity* entity_ = nullptr;
    Ogre::SceneNode* sceneNode_ = nullptr;

  public:
    RenderComponent();
    virtual ~RenderComponent();

    // interface for each render component render method
    virtual void render() = 0;

    virtual void setActive(bool active);
    void rotate(int degree, Ogre::Vector3 axis);

    // Getters and setters
    Ogre::Entity* getOgreEntity() const;
    void setOgreEntity(Ogre::Entity* e);

    Ogre::SceneNode* getSceneNode() const;
    void setSceneNode(Ogre::SceneNode* sn);

    // Destroys the PhysicsComponent, setting itself as inactive and
    // removing itself from the scene.
    virtual void destroy();
};
