#include "SpotLightRC.h"
#include "ComponentsManager.h"
#include "Entity.h"
#include "FactoriesFactory.h"
#include "OgreSDLContext.h"
#include "Scene.h"
#include "TransformComponent.h"
#include <Ogre.h>
#include <json.h>

// COMPONENT CODE
SpotLightRC::SpotLightRC() = default;

// Destroys the light
SpotLightRC::~SpotLightRC() { msM_->destroyLight(light_); }

// Creates the light
void SpotLightRC::setLight(const std::string& entityId) {
    msM_ = OgreSDLContext::getInstance()->getSceneManager();

    light_ = msM_->createLight(entityId + "Light");
    light_->setType(Ogre::Light::LT_DIRECTIONAL);
}

Ogre::Light* SpotLightRC::getLight() const { return light_; }

void SpotLightRC::setColour(const Ogre::Vector3 colour) {
    light_->setDiffuseColour(colour.x, colour.y, colour.z);
}

void SpotLightRC::setDirection(const Ogre::Vector3 dir) {
    sceneNode_->setDirection(Ogre::Vector3(dir.x, dir.y, dir.z));
}

void SpotLightRC::render() {}

// FACTORY INFRASTRUCTURE DEFINITION

SpotLightRCFactory::SpotLightRCFactory() = default;

Component* SpotLightRCFactory::create(Entity* _father, Json::Value& _data,
                                      Scene* _scene) {
    Ogre::SceneManager* mSM = OgreSDLContext::getInstance()->getSceneManager();
    SpotLightRC* light = new SpotLightRC();
    _scene->getComponentsManager()->addRC(light);

    light->setFather(_father);
    light->setScene(_scene);

    light->setLight(_father->getId());

    if (!_data["node"].isString())
        throw std::exception("SpotLightRC: node is not a string");
    light->setSceneNode(mSM->getRootSceneNode()->createChildSceneNode(
        _data["node"].asString()));
    light->getSceneNode()->attachObject(light->getLight());

    if (!_data["colour"].isArray())
        throw std::exception("SpotLightRC: colour is not an array");
    light->setColour(Ogre::Vector3(_data["colour"][0].asFloat(),
                                   _data["colour"][1].asFloat(),
                                   _data["colour"][2].asFloat()));

    if (!_data["direction"].isArray())
        throw std::exception("SpotLightRC: direction is not an array");
    light->setDirection(Ogre::Vector3(_data["direction"][0].asFloat(),
                                      _data["direction"][1].asFloat(),
                                      _data["direction"][2].asFloat()));

    return light;
}

DEFINE_FACTORY(SpotLightRC);
