#include "RenderComponent.h"
#include "ComponentsManager.h"
#include "OgreEntity.h"
#include "OgreSDLContext.h"
#include "OgreSceneManager.h"
#include "Scene.h"

RenderComponent::RenderComponent() : Component() {}

RenderComponent::~RenderComponent() {
    if (entity != nullptr)
        OgreSDLContext::getInstance()->getSceneManager()->destroyEntity(entity);
    if (sceneNode != nullptr)
        OgreSDLContext::getInstance()->getSceneManager()->destroySceneNode(
            sceneNode);
}

void RenderComponent::setActive(bool active) {
    Component::setActive(active);
    sceneNode->setVisible(active);
}

void RenderComponent::rotate(int degree, Ogre::Vector3 axis) {
    sceneNode->setOrientation(Ogre::Quaternion(Ogre::Degree(degree), axis));
}

// GETTERS AND SETTERS
Ogre::Entity* RenderComponent::getOgreEntity() { return entity; }
void RenderComponent::setOgreEntity(Ogre::Entity* e) { entity = e; }

Ogre::SceneNode* RenderComponent::getSceneNode() { return sceneNode; }
void RenderComponent::setSceneNode(Ogre::SceneNode* sn) { sceneNode = sn; }

void RenderComponent::destroy() {
    setActive(false);
    scene->getComponentsManager()->eraseRC(this);
}
