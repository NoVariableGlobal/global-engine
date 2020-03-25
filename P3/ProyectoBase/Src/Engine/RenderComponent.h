#pragma once
#include "Component.h"

// Abstract subcomponent from which every graphic component should inherit

namespace Ogre {
    class Entity;
    class SceneNode;
    typedef float Real;
    template <int dims, typename T> class Vector;
    typedef Vector<3, Real> Vector3;
} // namespace Ogre

class RenderComponent : public Component {
  protected:
    // entity and scene node of the object this render component belongs to
    Ogre::Entity* entity = nullptr;
    Ogre::SceneNode* sceneNode = nullptr;

  public:
    RenderComponent();
    virtual ~RenderComponent();

    // interface for each render component render method
    virtual void render() = 0;

    virtual void setActive(bool active);
	void rotate(int degree, Ogre::Vector3 axis);

    // Getters and setters
    Ogre::Entity* getOgreEntity();
    void setOgreEntity(Ogre::Entity* e);

    Ogre::SceneNode* getSceneNode();
    void setSceneNode(Ogre::SceneNode* sn);
};
