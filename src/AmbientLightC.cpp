#include "AmbientLightC.h"
#include "ComponentsManager.h"
#include "FactoriesFactory.h"
#include "OgreEntity.h"
#include "OgreSDLContext.h"
#include "Scene.h"
#include "TransformComponent.h"

#include <OgreSceneManager.h>
#include <json.h>

AmbientLightC::AmbientLightC() { currentColour_ = new Ogre::Vector3(); }

AmbientLightC::~AmbientLightC() { delete currentColour_; }

// COMPONENT CODE
void AmbientLightC::destroy() {
    setActive(false);
    scene_->getComponentsManager()->eraseDC(this);
}

void AmbientLightC::setActive(bool active) {
    active_ = active;
    if (active_)
        OgreSDLContext::getInstance()->getSceneManager()->setAmbientLight(
            Ogre::ColourValue(currentColour_->x, currentColour_->y,
                              currentColour_->z, 1.0));
    else
        OgreSDLContext::getInstance()->getSceneManager()->setAmbientLight(
            Ogre::ColourValue(0.0, 0.0, 0.0, 0.0));
}

void AmbientLightC::setColour(Ogre::Vector3 colour) {
    *currentColour_ = colour;

    OgreSDLContext::getInstance()->getSceneManager()->setAmbientLight(
        Ogre::ColourValue(currentColour_->x, currentColour_->y,
                          currentColour_->z, 1.0));
}

// FACTORY INFRASTRUCTURE DEFINITION

AmbientLightCFactory::AmbientLightCFactory() = default;

Component* AmbientLightCFactory::create(Entity* _father, Json::Value& _data,
                                        Scene* _scene) {
    AmbientLightC* ambientLight = new AmbientLightC();

    _scene->getComponentsManager()->addDC(ambientLight);

    ambientLight->setFather(_father);
    ambientLight->setScene(_scene);

    if (!_data["colour"].isArray())
        throw std::exception("SkyPlaneObjectRC: colour is not an array");
    if (!_data["colour"][0].isDouble())
        throw std::exception(
            "SkyPlaneObjectRC: colour is not an array of doubles");

    ambientLight->setColour(Ogre::Vector3(_data["colour"][0].asFloat(),
                                          _data["colour"][1].asFloat(),
                                          _data["colour"][2].asFloat()));

    return ambientLight;
}

DEFINE_FACTORY(AmbientLightC);
