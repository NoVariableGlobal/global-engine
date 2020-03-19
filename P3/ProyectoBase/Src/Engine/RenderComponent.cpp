#include "RenderComponent.h"
#include "OgreEntity.h"
#include "OgreSDLContext.h"
#include "OgreSceneManager.h"

RenderComponent::RenderComponent() : Component() {}

RenderComponent::~RenderComponent() {
    if (entity != nullptr)
        OgreSDLContext::getInstance()->getSceneManager()->destroyEntity(entity);
    if (sceneNode != nullptr)
        OgreSDLContext::getInstance()->getSceneManager()->destroySceneNode(
            sceneNode);
}

// GETTERS AND SETTERS
Ogre::Entity* RenderComponent::getOgreEntity() { return entity; }
void RenderComponent::setOgreEntity(Ogre::Entity* e) { entity = e; }

Ogre::SceneNode* RenderComponent::getSceneNode() { return sceneNode; }
void RenderComponent::setSceneNode(Ogre::SceneNode* sn) { sceneNode = sn; }
