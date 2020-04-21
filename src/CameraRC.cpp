#include "CameraRC.h"
#include "ComponentsManager.h"
#include "Entity.h"
#include "FactoriesFactory.h"
#include "Factory.h"
#include "OgreSDLContext.h"
#include "Scene.h"
#include "TransformComponent.h"

#include <Ogre.h>
#include <json.h>

// Constructor, se crea la camara se le asocia el viewport y se asocian todos lo
// sceneNode
CameraRC::CameraRC() = default;

CameraRC::~CameraRC() {
    // Destroys the camera and every viewport
    msM_->destroyCamera(camera_);
    OgreSDLContext::getInstance()->getRenderWindow()->removeAllViewports();

    delete cameraOffset_;
    delete look_;
}

// Creates the camera
void CameraRC::setCamera(const std::string& entityId) {
    msM_ = OgreSDLContext::getInstance()->getSceneManager();

    camera_ = msM_->createCamera(entityId + "Cam");
    camera_->setNearClipDistance(1);
    camera_->setFarClipDistance(10000);
    camera_->setAutoAspectRatio(true);
}

Ogre::Camera* CameraRC::getCamera() const { return camera_; }

// Sets the viewport
void CameraRC::setViewport(const Ogre::Vector3 colour) {
    vp_ =
        OgreSDLContext::getInstance()->getRenderWindow()->addViewport(camera_);
    vp_->setBackgroundColour(Ogre::ColourValue(colour.x, colour.y, colour.z));

    camera_->setAspectRatio(Ogre::Real(vp_->getActualWidth()) /
                            Ogre::Real(vp_->getActualHeight()));
}

void CameraRC::setCameraOffset(const Ogre::Vector3 offset) {
    delete cameraOffset_;
    cameraOffset_ = new Ogre::Vector3(offset);
}

void CameraRC::lookAt(const Ogre::Vector3 pos) {
    delete look_;
    look_ = new Ogre::Vector3(pos);

    sceneNode_->lookAt(pos, Ogre::Node::TS_WORLD);
}

void CameraRC::setTarget(const std::string target) { target_ = target; }

void CameraRC::setFollow(const Ogre::Vector3 follow) {
    followX_ = follow.x;
    followY_ = follow.y;
    followZ_ = follow.z;
}

void CameraRC::render() {
    const auto* transform = reinterpret_cast<TransformComponent*>(
        father_->getComponent("TransformComponent"));

    Ogre::Vector3 position;

    if (target_ != "") {
        const auto* transformTarget = reinterpret_cast<TransformComponent*>(
            scene_->getEntityById(target_)->getComponent("TransformComponent"));
        position = Ogre::Vector3(followX_ ? transformTarget->getPosition().x
                                          : transform->getPosition().x,
                                 followY_ ? transformTarget->getPosition().y
                                          : transform->getPosition().y,
                                 followZ_ ? transformTarget->getPosition().z
                                          : transform->getPosition().z);
    } else
        position = transform->getPosition();

    position += *cameraOffset_;

    sceneNode_->setPosition(position.x, position.y, position.z);
    lookAt(position);
}

// FACTORY INFRASTRUCTURE DEFINITION

CameraRCFactory::CameraRCFactory() = default;

Component* CameraRCFactory::create(Entity* _father, Json::Value& _data,
                                   Scene* _scene) {
    Ogre::SceneManager* mSM = OgreSDLContext::getInstance()->getSceneManager();
    CameraRC* camera = new CameraRC();
    _scene->getComponentsManager()->addRC(camera);

    camera->setFather(_father);
    camera->setScene(_scene);

    camera->setCamera(_father->getId());

    if (!_data["node"].isString())
        throw std::exception("CameraRC: node is not a string");

    camera->setSceneNode(mSM->getRootSceneNode()->createChildSceneNode(
        _data["node"].asString()));
    camera->getSceneNode()->attachObject(camera->getCamera());

    if (!_data["viewportColour"].isArray())
        throw std::exception("CameraRC: viewportColour is not an array");
    camera->setViewport(Ogre::Vector3(_data["viewportColour"][0].asFloat(),
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
    if (_data["lookAt"].isArray())
        camera->lookAt(Ogre::Vector3(_data["lookAt"][0].asFloat(),
                                     _data["lookAt"][1].asFloat(),
                                     _data["lookAt"][2].asFloat()));

    if (!_data["targetId"].isString())
        throw std::exception("CameraRC: targetId is not a string.");
    if (_data["targetId"].asString() != "none") {
        camera->setTarget(_data["targetId"].asString());

        if (!_data["follow"].isArray() || !_data["follow"][0].isBool())
            throw std::exception("CameraRC: follow is not an array or is "
                                 "not a boolean array.");
        camera->setFollow(Ogre::Vector3(_data["follow"][0].asBool(),
                                        _data["follow"][1].asBool(),
                                        _data["follow"][2].asBool()));
    }

    return camera;
}

DEFINE_FACTORY(CameraRC);
