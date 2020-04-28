#include "SkyPlaneObjectC.h"
#include "ComponentsManager.h"
#include "Entity.h"
#include "FactoriesFactory.h"
#include "OgreEntity.h"
#include "OgreSDLContext.h"
#include "Scene.h"
#include "TransformComponent.h"

#include <OgreSceneManager.h>
#include <json.h>

// COMPONENT CODE
void SkyPlaneObjectC::destroy() {
    setActive(false);
    scene_->getComponentsManager()->eraseDC(this);
}

void SkyPlaneObjectC::setActive(bool active) {
    active_ = active;
    OgreSDLContext::getInstance()->getSceneManager()->setSkyPlaneEnabled(
        active_);
}

void SkyPlaneObjectC::setSkyPlane(std::string normal, float distance,
                                     float bow, std::string material) {
    Ogre::Vector3 n;
    if (normal == "X")
        n = Ogre::Vector3::UNIT_X;
    else if (normal == "-X")
        n = Ogre::Vector3::NEGATIVE_UNIT_X;
    else if (normal == "Y")
        n = Ogre::Vector3::UNIT_Y;
    else if (normal == "-Y")
        n = Ogre::Vector3::NEGATIVE_UNIT_Y;
    else if (normal == "Z")
        n = Ogre::Vector3::UNIT_Z;
    else if (normal == "-Z")
        n = Ogre::Vector3::NEGATIVE_UNIT_Z;
    else
        throw std::exception("SkyPlaneObjectRC: not a correct normal. The "
                             "options are: X, -X, Y, -Y, Z, -Z");

    OgreSDLContext::getInstance()->getSceneManager()->setSkyPlane(
        true, Ogre::Plane(n, distance), material, 1, 1, true, bow, 100, 100);
}

// FACTORY INFRASTRUCTURE DEFINITION

SkyPlaneObjectCFactory::SkyPlaneObjectCFactory() = default;

Component* SkyPlaneObjectCFactory::create(Entity* _father, Json::Value& _data,
                                          Scene* _scene) {
    SkyPlaneObjectC* planeObject = new SkyPlaneObjectC();

    _scene->getComponentsManager()->addDC(planeObject);

    planeObject->setFather(_father);
    planeObject->setScene(_scene);

    if (!_data["normal"].isString())
        throw std::exception("SkyPlaneObjectRC: normal is not a string");

    if (!_data["distance"].isDouble())
        throw std::exception("SkyPlaneObjectRC: distance is not a float");

    if (!_data["bow"].isDouble())
        throw std::exception("SkyPlaneObjectRC: bow is not a float");

    if (!_data["material"].isString())
        throw std::exception("SkyPlaneObjectRC: material is not a string");

    planeObject->setSkyPlane(
        _data["normal"].asString(), _data["distance"].asDouble(),
        _data["bow"].asDouble(), _data["material"].asString());

    return planeObject;
}

DEFINE_FACTORY(SkyPlaneObjectC);
