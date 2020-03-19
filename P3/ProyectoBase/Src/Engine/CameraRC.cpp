#include "CameraRC.h"
#include "ComponentsManager.h"
#include "Entity.h"
#include "FactoriesFactory.h"
#include "Factory.h"
#include "OgreSDLContext.h"
#include "Scene.h"
#include "TransformComponent.h"

#include <Ogre.h>
#include <OgreSceneManager.h>

#include <json.h>

// Constructor, se crea la camara se le asocia el viewport y se asocian todos lo
// sceneNode
CameraRC::CameraRC() : RenderComponent() {}

CameraRC::~CameraRC() {
    // Destroys the camera and every viewport
    _msM->destroyCamera(camera);
    OgreSDLContext::getInstance()->getRenderWindow()->removeAllViewports();

    delete cameraOffset;
    delete look;
}

// Creates the camera
void CameraRC::setCamera(std::string _entityID) {
    _msM = OgreSDLContext::getInstance()->getSceneManager();

    camera = _msM->createCamera(_entityID + "Cam");
    camera->setNearClipDistance(1);
    camera->setFarClipDistance(10000);
    camera->setAutoAspectRatio(true);
}

Ogre::Camera* CameraRC::getCamera() { return camera; }

// Sets the viewport
void CameraRC::setViewport(Ogre::Vector3 _colour) {
    vp = OgreSDLContext::getInstance()->getRenderWindow()->addViewport(camera);
    vp->setBackgroundColour(Ogre::ColourValue(_colour.x, _colour.y, _colour.z));

    camera->setAspectRatio(Ogre::Real(vp->getActualWidth()) /
                           Ogre::Real(vp->getActualHeight()));
}

void CameraRC::setCameraOffset(Ogre::Vector3(_offset)) {
    if (cameraOffset != nullptr)
        delete cameraOffset;
    cameraOffset = new Ogre::Vector3(_offset);
}

void CameraRC::lookAt(Ogre::Vector3 _pos) {
    if (look != nullptr)
        delete look;
    look = new Ogre::Vector3(_pos);

    sceneNode->lookAt(_pos, Ogre::Node::TS_WORLD);
}

void CameraRC::render() {
    const auto transform = dynamic_cast<TransformComponent*>(
        father->getComponent("TransformComponent"));
    const auto position = transform->getPosition() + *cameraOffset;

    sceneNode->setPosition(position.x, position.y, position.z);
    lookAt(position);
}

// FACTORY INFRASTRUCTURE
class CameraRCFactory final : public ComponentFactory {
  public:
    CameraRCFactory() = default;

    Component* create(Entity* _father, Json::Value& _data,
                      Scene* scene) override {
        Ogre::SceneManager* mSM =
            OgreSDLContext::getInstance()->getSceneManager();
        CameraRC* camera = new CameraRC();
        scene->getComponentsManager()->addRC(camera);

        camera->setFather(_father);
        camera->setScene(scene);

        camera->setCamera(_father->getId());

        if (!_data["node"].isString())
            throw std::exception("CameraRC: node is not a string");

        camera->setSceneNode(mSM->getRootSceneNode()->createChildSceneNode(
            _data["node"].asString()));
        camera->getSceneNode()->attachObject(camera->getCamera());

        if (!_data["viewportColour"].isArray())
            throw std::exception("CameraRC: viewportColour is not an array");
        camera->setViewport(
            Ogre::Vector3(_data["viewportColour"][0].asFloat(),
                          _data["viewportColour"][1].asFloat(),
                          _data["viewportColour"][2].asFloat()));

        if (!_data["offset"].isArray())
            throw std::exception("CameraRC: offset is not an array");
        camera->setCameraOffset(Ogre::Vector3(_data["offset"][0].asFloat(),
                                              _data["offset"][1].asFloat(),
                                              _data["offset"][2].asFloat()));

        TransformComponent* transform = dynamic_cast<TransformComponent*>(
            _father->getComponent("TransformComponent"));
        camera->getSceneNode()->setPosition(transform->getPosition());

        if (!_data["lookAt"].isArray() && !_data["lookAt"].isString())
            throw std::exception("CameraRC: lookAt is not an array. If you do "
                                 "not want an array, use a string 'none'");
        else if (_data["lookAt"].isArray())
            camera->lookAt(Ogre::Vector3(_data["lookAt"][0].asFloat(),
                                         _data["lookAt"][1].asFloat(),
                                         _data["lookAt"][2].asFloat()));

        return camera;
    }
};

REGISTER_FACTORY("CameraRC", CameraRC);
