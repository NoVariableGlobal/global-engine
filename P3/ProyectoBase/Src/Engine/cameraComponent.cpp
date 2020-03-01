#include "CameraComponent.h"
#include <OgreSceneManager.h>

//Constructor, se crea la camara se le asocia el viewport y se asocian todos lo sceneNode
CameraComponent::CameraComponent(Ogre::SceneManager* _mSM) /* : Component() */
{
	camera = _mSM->createCamera("Cam");
	camera->setNearClipDistance(1);
	camera->setFarClipDistance(10000);
	camera->setAutoAspectRatio(true);

	mCamNode = _mSM->getRootSceneNode()->createChildSceneNode("nCam");
	mCamNode->attachObject(camera);

	mCamNode->setPosition(0, 0, 1000);
	mCamNode->lookAt(Ogre::Vector3(0, 0, 0), Ogre::Node::TS_WORLD);

	vp = getRenderWindow()->addViewport(camera);
	vp->setBackgroundColour(Ogre::ColourValue(0.5, 0.5, 1));

	light = _mSM->createLight("Light");
	light->setType(Ogre::Light::LT_DIRECTIONAL);
	light->setDiffuseColour(1, 1, 1);

	mLightNode = _mSM->getRootSceneNode()->createChildSceneNode("nLight");
	mLightNode->attachObject(light);

	mLightNode->setDirection(Ogre::Vector3(1, -1, -1));

	mCamMgr = new OgreBites::CameraMan(mCamNode);
	addInputListener(mCamMgr);
	mCamMgr->setStyle(OgreBites::CS_ORBIT);

	cameraOffset = Ogre::Vector3(0, 0, 0);
}

CameraComponent::~CameraComponent()
{
	delete mCamMgr; mCamMgr = nullptr;
}

void CameraComponent::setNodeTarget(Ogre::SceneNode* _target)
 {
	target = _target;
 }

void CameraComponent::setCameraOffset(Ogre::Vector3(_offset))
{
	cameraOffset = _offset;
}
 
void CameraComponent::setPosition(Ogre::Vector3 pos)
 {
	mCamNode->setPosition(pos);
 }
 
void CameraComponent::lookAt(Ogre::Vector3 pos)
 {
	mCamNode->lookAt(pos, Ogre::Node::TS_WORLD);
 }

void CameraComponent::updateCamera()
{
	if (target != nullptr)
	{
		setPosition(target->getPosition() + cameraOffset);
		lookAt(target->getPosition());
	}
}
