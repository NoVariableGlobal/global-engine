#pragma once
#include "Ogre.h"

class Component;
class Camera;
class SceneNode;
class CameraMan;
class Viewport;
class SceneManager;
class OgreContext;

// TO DO: fix errors related to Ogre libraries and ApplicationContext
class CameraObject
{
private:
	Ogre::Camera* camera = nullptr;
	Ogre::SceneNode* mCamNode = nullptr;
	Ogre::Viewport* vp = nullptr;
	Ogre::Light* light = nullptr;
	Ogre::SceneNode* mLightNode = nullptr;

	// who the camera follows
	Ogre::SceneNode* target = nullptr;
	// camera offset relative to followed object
	Ogre::Vector3 cameraOffset;

public:
	CameraObject(Ogre::SceneManager* _mSM);
	~CameraObject();

	// camera follows a specific node
	void setNodeTarget(Ogre::SceneNode* _target);
	// set camera offset
	void setCameraOffset(Ogre::Vector3(_offset));
	// set camera position
	void setPosition(Ogre::Vector3 _pos);
	// set camera direction
	void lookAt(Ogre::Vector3 _pos);

	// called each frame
	void updateCamera();

};