#include "RenderComponent.h"
#include "ComponentsManager.h"
#include "OgreEntity.h"
#include "OgreSDLContext.h"
#include "OgreSceneManager.h"
#include "Scene.h"

RenderComponent::RenderComponent() = default;

RenderComponent::~RenderComponent() {
    if (entity_ != nullptr)
        OgreSDLContext::getInstance()->getSceneManager()->destroyEntity(
            entity_);
    if (sceneNode_ != nullptr)
        OgreSDLContext::getInstance()->getSceneManager()->destroySceneNode(
            sceneNode_);
}

void RenderComponent::setActive(const bool active) {
    Component::setActive(active);
    sceneNode_->setVisible(active);
}

void RenderComponent::rotate(const int degree, const Ogre::Vector3 axis) {
    sceneNode_->setOrientation(
        Ogre::Quaternion(Ogre::Degree(static_cast<Ogre::Real>(degree)), axis));
}

// GETTERS AND SETTERS
Ogre::Entity* RenderComponent::getOgreEntity() const { return entity_; }
void RenderComponent::setOgreEntity(Ogre::Entity* e) { entity_ = e; }

Ogre::SceneNode* RenderComponent::getSceneNode() const { return sceneNode_; }
void RenderComponent::setSceneNode(Ogre::SceneNode* sn) { sceneNode_ = sn; }

void RenderComponent::destroy() {
    setActive(false);
    scene_->getComponentsManager()->eraseRC(this);
}
