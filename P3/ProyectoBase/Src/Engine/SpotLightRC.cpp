#include <json.h>

#include "ComponentsManager.h"
#include "Entity.h"
#include "FactoriesFactory.h"
#include "Factory.h"
#include "OgreEntity.h"
#include "OgreSDLContext.h"
#include "OgreSceneManager.h"
#include "Scene.h"
#include "SpotLightRC.h"
#include "TransformComponent.h"

// COMPONENT CODE
SpotLightRC::SpotLightRC() {}

// Destroys the light
SpotLightRC::~SpotLightRC() { _msM->destroyLight(light); }
// Creates the light
void SpotLightRC::setLight(std::string _entityID) {
    _msM = OgreSDLContext::getInstance()->getSceneManager();

    light = _msM->createLight(_entityID + "Light");
    light->setType(Ogre::Light::LT_DIRECTIONAL);
}

Ogre::Light* SpotLightRC::getLight() { return light; }

void SpotLightRC::setColour(Ogre::Vector3 _colour) {
    light->setDiffuseColour(_colour.x, _colour.y, _colour.z);
}

void SpotLightRC::setDirection(Ogre::Vector3 _dir) {
    sceneNode->setDirection(Ogre::Vector3(_dir.x, _dir.y, _dir.z));
}

void SpotLightRC::render() {}

// FACTORY INFRASTRUCTURE
class SpotLightRCFactory final : public ComponentFactory {
  public:
    SpotLightRCFactory() = default;

    Component* create(Entity* _father, Json::Value& _data,
                      Scene* _scene) override {
        Ogre::SceneManager* mSM =
            OgreSDLContext::getInstance()->getSceneManager();
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
};

REGISTER_FACTORY("SpotLightRC", SpotLightRC);