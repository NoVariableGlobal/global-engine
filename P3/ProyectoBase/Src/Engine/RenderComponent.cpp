#include "RenderComponent.h"
#include "OgreEntity.h"
#include "OgreSceneManager.h"
#include "OgreSDLContext.h"

RenderComponent::RenderComponent() : Component() {}

RenderComponent::~RenderComponent() 
{
	OgreSDLContext::getInstance()->getSceneManager()->destroyEntity(_entity);
	OgreSDLContext::getInstance()->getSceneManager()->destroySceneNode(_sceneNode);
}

// GETTERS AND SETTERS
Ogre::Entity* RenderComponent::getOgreEntity() { return _entity; }
void RenderComponent::setOgreEntity(Ogre::Entity* e) { _entity = e; }

Ogre::SceneNode* RenderComponent::getSceneNode() { return _sceneNode; }
void RenderComponent::setSceneNode(Ogre::SceneNode* sn) { _sceneNode = sn; }