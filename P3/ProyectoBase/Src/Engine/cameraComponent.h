#pragma once

#include <Ogre.h>

class Component;
class Camera;
class SceneNode;
class CameraMan;
class Viewport;
class SceneManager;
class ApplicationContext;

class CameraComponent /*: public Component */
{
	private:
		Ogre::Camera* camera = nullptr;
		Ogre::SceneNode* mCamNode = nullptr;
		Ogre::Viewport* vp = nullptr;
		Ogre::Light* light = nullptr;
		Ogre::SceneNode* mLightNode = nullptr;
		OgreBites::CameraMan* mCamMgr = nullptr;


	public:
		CameraComponent(Ogre::SceneManager* _mSM);
		~CameraComponent();

		// camera follows a specific node
		void setNodeTarget(Ogre::SceneNode* _target);
		// set camera position
		void setPosition(Ogre::Vector3 _pos);
		// set camera direction
		void lookAt(Ogre::Vector3 _pos);

		// called each frame
		void updateCamera();

};