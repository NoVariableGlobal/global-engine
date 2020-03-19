#pragma once
#include "Component.h"

// Abstract subcomponent from which every graphic component should inherit

namespace Ogre {
    class Entity;
    class SceneNode;
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

    // Getters and setters
    Ogre::Entity* getOgreEntity();
    void setOgreEntity(Ogre::Entity* e);

    Ogre::SceneNode* getSceneNode();
    void setSceneNode(Ogre::SceneNode* sn);
};
