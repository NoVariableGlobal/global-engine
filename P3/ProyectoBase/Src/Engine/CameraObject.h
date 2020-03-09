#pragma once

namespace Ogre
{
	class Component;
	class Camera;
	class SceneNode;
	class CameraMan;
	class Viewport;
	class SceneManager;
	class OgreSDLContext;
	class Light;

	typedef float Real;
	template <int dims, typename T> class Vector;
	typedef Vector<3, Real> Vector3;
}

class TransformComponent;

// TO DO: fix errors related to Ogre libraries and ApplicationContext
class CameraObject
{
private:
	Ogre::SceneManager* _msM;
	Ogre::Camera* camera = nullptr;
	Ogre::SceneNode* mCamNode = nullptr;
	Ogre::Viewport* vp = nullptr;
	Ogre::Light* light = nullptr;
	Ogre::SceneNode* mLightNode = nullptr;

	// who the camera follows
	TransformComponent* target = nullptr;
	// camera offset relative to followed object
	Ogre::Vector3* cameraOffset = nullptr;

public:
	CameraObject();
	~CameraObject();

	// camera follows a specific node
	void setTarget(TransformComponent* _target);
	// set camera offset
	void setCameraOffset(Ogre::Vector3(_offset));
	// set camera position
	void setPosition(Ogre::Vector3 _pos);
	// set camera direction
	void lookAt(Ogre::Vector3 _pos);

	// called each frame
	void updateCamera();

};