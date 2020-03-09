#include "CameraObject.h"
#include "TransformComponent.h"

#include <OgreSceneManager.h>
#include "OgreSDLContext.h"
#include "Ogre.h"

#include "OgreSDLContext.h"
#include "Ogre.h"

//Constructor, se crea la camara se le asocia el viewport y se asocian todos lo sceneNode
CameraObject::CameraObject() /* : Component() */
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

	// ambient light
	_msM->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));

	light = _msM->createLight("Light");
	light->setType(Ogre::Light::LT_DIRECTIONAL);
	light->setDiffuseColour(1, 1, 1);

	mLightNode = _msM->getRootSceneNode()->createChildSceneNode("nLight");
	mLightNode->attachObject(light);

	mLightNode->setDirection(Ogre::Vector3(1, -1, -1));

	cameraOffset = new Ogre::Vector3(0, 0, 0);
}

CameraObject::~CameraObject() 
{
	delete cameraOffset;
}

void CameraObject::setTarget(TransformComponent* _target)
{
	target = _target;
}

void CameraObject::setCameraOffset(Ogre::Vector3(_offset))
{
	*cameraOffset = _offset;
}

void CameraObject::setPosition(Ogre::Vector3 _pos)
{
	mCamNode->setPosition(_pos);
}

void CameraObject::lookAt(Ogre::Vector3 _pos)
{
	mCamNode->lookAt(_pos, Ogre::Node::TS_WORLD);
}

void CameraObject::updateCamera()
{
	if (target != nullptr)
	{
		setPosition(target->getPosition() + *cameraOffset);
		lookAt(target->getPosition());
	}
}
