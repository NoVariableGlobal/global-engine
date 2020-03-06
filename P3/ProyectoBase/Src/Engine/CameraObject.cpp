#include "CameraObject.h"

#include <OgreSceneManager.h>

#include "OgreSDLContext.h"
#include <OgreShaderGenerator.h>
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

	mCamNode->setPosition(0, 0, 300);
	mCamNode->lookAt(Ogre::Vector3(0, 0, 0), Ogre::Node::TS_WORLD);

	vp = OgreSDLContext::getInstance()->getRenderWindow()->addViewport(camera);
	vp->setMaterialScheme(Ogre::RTShader::ShaderGenerator::DEFAULT_SCHEME_NAME); // use the default material scheme that the RTSS uses
	vp->setBackgroundColour(Ogre::ColourValue(0.5, 0.5, 1));

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

void CameraObject::setNodeTarget(Ogre::SceneNode* _target)
{
	target = _target;
}

void CameraObject::setCameraOffset(Ogre::Vector3(_offset))
{
	*cameraOffset = _offset;
}

void CameraObject::setPosition(Ogre::Vector3 pos)
{
	mCamNode->setPosition(pos);
}

void CameraObject::lookAt(Ogre::Vector3 pos)
{
	mCamNode->lookAt(pos, Ogre::Node::TS_WORLD);
}

void CameraObject::updateCamera()
{
	if (target != nullptr)
	{
		setPosition(target->getPosition() + *cameraOffset);
		lookAt(target->getPosition());
	}
}
