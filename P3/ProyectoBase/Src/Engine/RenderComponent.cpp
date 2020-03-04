#include "RenderComponent.h"
#include "OgreEntity.h"
#include "OgreSceneManager.h"

RenderComponent::RenderComponent() : Component() {}

RenderComponent::~RenderComponent() {}

// GETTERS AND SETTERS
Ogre::Entity* RenderComponent::getOgreEntity() { return _entity; }
void RenderComponent::setOgreEntity(Ogre::Entity* e) { _entity = e; }

Ogre::SceneNode* RenderComponent::getSceneNode() { return _sceneNode; }
void RenderComponent::setSceneNode(Ogre::SceneNode* sn) { _sceneNode = sn; }