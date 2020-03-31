#include "TridimensionalObjectRC.h"
#include "ComponentsManager.h"
#include "Entity.h"
#include "OgreEntity.h"
#include "OgreSDLContext.h"
#include "OgreSceneManager.h"
#include "Scene.h"
#include "FactoriesFactory.h"
#include "TransformComponent.h"
#include <json.h>

// COMPONENT CODE
TridimensionalObjectRC::TridimensionalObjectRC() {}

TridimensionalObjectRC::~TridimensionalObjectRC() {}

void TridimensionalObjectRC::destroy() {
    setActive(false);
    scene->getComponentsManager()->eraseRC(this);
}

// Updates the node position as our father transform
void TridimensionalObjectRC::render() {
    TransformComponent* transform = dynamic_cast<TransformComponent*>(
        father->getComponent("TransformComponent"));
    getSceneNode()->setPosition(transform->getPosition());
    getSceneNode()->setScale(transform->getScale());
}

void TridimensionalObjectRC::setMaterial(std::string material) {
    entity->setMaterialName(material);
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
