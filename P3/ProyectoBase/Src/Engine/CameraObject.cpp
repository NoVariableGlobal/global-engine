#include "CameraObject.h"
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
CameraRC::CameraRC() : RenderComponent()
{
	_msM = OgreSDLContext::getInstance()->getSceneManager();
	camera = _msM->createCamera("Cam");
	camera->setNearClipDistance(1);
	camera->setFarClipDistance(10000);
	camera->setAutoAspectRatio(true);

	mCamNode = _msM->getRootSceneNode()->createChildSceneNode("nCam");
	mCamNode->attachObject(camera);

	vp = OgreSDLContext::getInstance()->getRenderWindow()->addViewport(camera);
	vp->setBackgroundColour(Ogre::ColourValue(0, 0, 0));

	camera->setAspectRatio(Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));

	cameraOffset = new Ogre::Vector3(0, 0, 0);

	// ambient light
	_msM->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));

	light = _msM->createLight("Light");
	light->setType(Ogre::Light::LT_DIRECTIONAL);
	light->setDiffuseColour(1, 1, 1);

	mLightNode = _msM->getRootSceneNode()->createChildSceneNode("nLight");
	mLightNode->attachObject(light);

	mLightNode->setDirection(Ogre::Vector3(1, -1, -1));
}

CameraRC::~CameraRC() 
{
	delete cameraOffset;
}

void CameraRC::setTarget(TransformComponent* _target)
{
	target = _target;
}

void CameraRC::setCameraOffset(Ogre::Vector3(_offset))
{
	*cameraOffset = _offset;
}

void CameraRC::lookAt(Ogre::Vector3 _pos)
{
	mCamNode->lookAt(_pos, Ogre::Node::TS_WORLD);
}

void CameraRC::render()
{
	if (target != nullptr)
	{
		//setPosition(target->getPosition() + *cameraOffset);
		lookAt(target->getPosition());
	}
}

// FACTORY INFRASTRUCTURE
class CameraRCFactory : public ComponentFactory {
public:
	CameraRCFactory() {};

	virtual Component* create(Entity* father, Json::Value& _data, ComponentsManager* componentManager)
	{
		Ogre::SceneManager* mSM = OgreSDLContext::getInstance()->getSceneManager();
		CameraRC* camera = new CameraRC();

		camera->setFather(father);
		camera->setOgreEntity(mSM->createEntity(_data["mesh"].asString()));
		camera->setSceneNode(mSM->getRootSceneNode()->createChildSceneNode(_data["node"].asString()));
		camera->getSceneNode()->attachObject(camera->getOgreEntity());

		TransformComponent* transform = dynamic_cast<TransformComponent*>(father->getComponent("TransformComponent"));
		camera->getSceneNode()->setPosition(transform->getPosition());
		camera->getSceneNode()->setScale(transform->getScale());

		// Pendiente de unificar un metodo con las fisicas y otros que necesiten rotacion
		//Ogre::Vector3 ori = transform->getOrientation();
		//tridimensionalObject->getSceneNode()->setOrientation(0, ori.x, ori.y, ori.z);

		componentManager->addRC(camera);
		return camera;
	};
};

REGISTER_FACTORY("CameraRC", CameraRC);
