#pragma once

#include <RenderComponent.h>

#include <string>

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
class CameraRC : public RenderComponent
{
	private:
		Ogre::SceneManager* _msM;
		Ogre::Camera* camera = nullptr;
		Ogre::SceneNode* mCamNode = nullptr;
		Ogre::Viewport* vp = nullptr;
		Ogre::Light* light = nullptr;
		Ogre::SceneNode* mLightNode = nullptr;

		// camera offset relative to followed object
		Ogre::Vector3* cameraOffset = nullptr;

	public:
		CameraRC();
		~CameraRC();

		// set camera
		void setCamera(std::string _entityID);
		// get camera
		Ogre::Camera* getCamera();
		// set viewport
		void setViewport();
		// set camera offset
		void setCameraOffset(Ogre::Vector3(_offset));
		// set camera direction
		void lookAt(Ogre::Vector3 _pos);

		// called each frame
		virtual void render();
};