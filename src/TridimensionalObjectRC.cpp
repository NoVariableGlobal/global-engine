#include "TridimensionalObjectRC.h"
#include "ComponentsManager.h"
#include "Entity.h"
#include "FactoriesFactory.h"
#include "OgreSDLContext.h"
#include "Scene.h"
#include "TransformComponent.h"
#include <Ogre.h>
#include <json.h>

// Updates the node position as our father transform
void TridimensionalObjectRC::render() {
    auto* transform = reinterpret_cast<TransformComponent*>(
        father_->getComponent("TransformComponent"));
    getSceneNode()->setPosition(transform->getPosition());
    getSceneNode()->setScale(transform->getScale());

    setRotation(transform->getOrientation());
}

void TridimensionalObjectRC::setMaterial(const std::string material) {
    entity_->setMaterialName(material);
}

void TridimensionalObjectRC::setRotation(const Ogre::Vector3 r) {
    // Reset original orientation
    resetRotation();

    // Apply new rotation
    getSceneNode()->pitch(Ogre::Degree(r.x), Ogre::Node::TS_LOCAL);
    getSceneNode()->yaw(Ogre::Degree(r.y), Ogre::Node::TS_LOCAL);
    getSceneNode()->roll(Ogre::Degree(r.z), Ogre::Node::TS_LOCAL);

    // Save new rotation in transform component
    reinterpret_cast<TransformComponent*>(
        father_->getComponent("TransformComponent"))
        ->setOrientation(r);
}

void TridimensionalObjectRC::resetRotation() {
    TransformComponent* transform = reinterpret_cast<TransformComponent*>(
        father_->getComponent("TransformComponent"));
    Ogre::SceneNode* node = getSceneNode();
    Ogre::Vector3 r = transform->getOriginalOrientation();

    // Set orientation to 0, 0, 0
    node->setOrientation(
        Ogre::Quaternion(Ogre::Degree(0), Ogre::Vector3(1, 1, 1)));

    // Reset orientation to its original
    node->pitch(Ogre::Degree(r.x), Ogre::Node::TS_LOCAL);
    node->yaw(Ogre::Degree(r.y), Ogre::Node::TS_LOCAL);
    node->roll(Ogre::Degree(r.z), Ogre::Node::TS_LOCAL);

    // Save orientation in transform component
    transform->setOrientation(transform->getOriginalOrientation());
}

// FACTORY INFRASTRUCTURE DEFINITION

TridimensionalObjectRCFactory::TridimensionalObjectRCFactory() = default;

Component* TridimensionalObjectRCFactory::create(Entity* _father,
                                                 Json::Value& _data,
                                                 Scene* _scene) {
    Ogre::SceneManager* mSM = OgreSDLContext::getInstance()->getSceneManager();
    TridimensionalObjectRC* tridimensionalObject = new TridimensionalObjectRC();
    _scene->getComponentsManager()->addRC(tridimensionalObject);

    tridimensionalObject->setFather(_father);
    tridimensionalObject->setScene(_scene);

    if (!_data["mesh"].isString())
        throw std::exception("TridimensionalObjectRC: mesh is not a string");
    tridimensionalObject->setOgreEntity(
        mSM->createEntity(_data["mesh"].asString()));

    if (!_data["node"].isString())
        throw std::exception("TridimensionalObjectRC: node is not a string");
    tridimensionalObject->setSceneNode(
        mSM->getRootSceneNode()->createChildSceneNode(_data["node"].asString() +
                                                      _father->getId()));

    if (!_data["material"].isString())
        throw std::exception(
            "TridimensionalObjectRC: material is not a string");
    else if (_data["material"].asString() != "none")
        tridimensionalObject->setMaterial(_data["material"].asString());

    tridimensionalObject->getSceneNode()->attachObject(
        tridimensionalObject->getOgreEntity());

    TransformComponent* transform = dynamic_cast<TransformComponent*>(
        _father->getComponent("TransformComponent"));
    tridimensionalObject->getSceneNode()->setPosition(transform->getPosition());
    tridimensionalObject->getSceneNode()->setScale(transform->getScale());

    return tridimensionalObject;
}

DEFINE_FACTORY(TridimensionalObjectRC);
