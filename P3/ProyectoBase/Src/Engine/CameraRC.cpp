#include "CameraRC.h"
#include "TransformComponent.h"
#include "Factory.h"
#include "FactoriesFactory.h"
#include "ComponentsManager.h"
#include "Entity.h"
#include "OgreSDLContext.h"

#include <OgreSceneManager.h>
#include <Ogre.h>

#include <json.h>

//Constructor, se crea la camara se le asocia el viewport y se asocian todos lo sceneNode
CameraRC::CameraRC() : RenderComponent() {}

CameraRC::~CameraRC() 
{
	delete cameraOffset;
	delete look;
}

void CameraRC::setCamera(std::string _entityID)
{
	_msM = OgreSDLContext::getInstance()->getSceneManager();

	camera = _msM->createCamera(_entityID + "Cam");
	camera->setNearClipDistance(1);
	camera->setFarClipDistance(10000);
	camera->setAutoAspectRatio(true);
}

Ogre::Camera* CameraRC::getCamera() { return camera; }

void CameraRC::setViewport(Ogre::Vector3 _colour)
{
	vp = OgreSDLContext::getInstance()->getRenderWindow()->addViewport(camera);
	vp->setBackgroundColour(Ogre::ColourValue(_colour.x, _colour.y, _colour.z));

	camera->setAspectRatio(Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));
}

void CameraRC::setCameraOffset(Ogre::Vector3(_offset))
{
	if (cameraOffset != nullptr)
		delete cameraOffset;
	cameraOffset = new Ogre::Vector3(_offset);
}

void CameraRC::lookAt(Ogre::Vector3 _pos)
{
	if (look != nullptr)
		delete look;
	look = new Ogre::Vector3(_pos);

	sceneNode->lookAt(_pos, Ogre::Node::TS_WORLD);
}

void CameraRC::render()
{
	Ogre::Vector3* position = &(dynamic_cast<TransformComponent*>(father->getComponent("TransformComponent"))->getPosition() + *cameraOffset);

	sceneNode->setPosition(position->x, position->y, position->z);
	lookAt(*position);
}

// FACTORY INFRASTRUCTURE
class CameraRCFactory : public ComponentFactory {
public:
	CameraRCFactory() {};

	virtual Component* create(Entity* _father, Json::Value& _data, ComponentsManager* _componentManager)
	{
		Ogre::SceneManager* mSM = OgreSDLContext::getInstance()->getSceneManager();
		CameraRC* camera = new CameraRC();

		camera->setFather(_father);

		camera->setCamera(_father->getId());

		if (!_data["node"].isString()) { /*EXCEPCION*/ }
		camera->setSceneNode(mSM->getRootSceneNode()->createChildSceneNode(_data["node"].asString()));
		camera->getSceneNode()->attachObject(camera->getCamera());

		if (!_data["viewportColour"].isArray()) { /*EXCEPCION*/ }
		camera->setViewport(Ogre::Vector3(_data["viewportColour"][0].asInt(), _data["viewportColour"][1].asInt(), _data["viewportColour"][2].asInt()));

		if (!_data["offset"].isArray()) { /*EXCEPCION*/ }
		camera->setCameraOffset(Ogre::Vector3(_data["offset"][0].asInt(), _data["offset"][1].asInt(), _data["offset"][2].asInt()));

		TransformComponent* transform = dynamic_cast<TransformComponent*>(_father->getComponent("TransformComponent"));
		camera->getSceneNode()->setPosition(transform->getPosition());

		if (!_data["lookAt"].isArray() && !_data["lookAt"].isString()) { /*EXCEPCION*/ }
		else if(_data["lookAt"].isArray())
			camera->lookAt(Ogre::Vector3(_data["lookAt"][0].asInt(), _data["lookAt"][1].asInt(), _data["lookAt"][2].asInt()));


		_componentManager->addRC(camera);

		return camera;
	};
};

REGISTER_FACTORY("CameraRC", CameraRC);
