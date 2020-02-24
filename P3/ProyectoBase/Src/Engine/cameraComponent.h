#pragma once

class Component;
class Camera;
class SceneNode;
class CameraMan;
class Viewport;
class SceneManager;

class CameraComponent : public Component
{
	private:
		Ogre::Camera* camera = nullptr;
		Ogre::SceneNode* mCamNode = nullptr;
		OgreBites::CameraMan* mCamMgr = nullptr;
		Ogre::Viewport* vp = nullptr;

	public:
		void CameraComponent(Ogre::SceneManager* mSM);
		void setNodeTarget(Ogre::SceneNode* target);
		void setPosition(Vector3 pos);
		void setDirection(Vector3 dir);

};