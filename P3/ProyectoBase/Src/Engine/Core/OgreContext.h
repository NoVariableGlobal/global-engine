#pragma once

#include <OgreRoot.h>
#include <string>

class OgreContext
{
	private:
		static OgreContext* _instance;

	protected:
		Ogre::Root* mRoot = nullptr;
		Ogre::String mResourcesCfg;
		Ogre::String mPluginsCfg;

		Ogre::RenderWindow* mWindow = nullptr;
		Ogre::SceneManager* mSM = nullptr;
		Ogre::SceneNode* mCam = nullptr;
		Ogre::SceneNode* mLight = nullptr;

	public:
		OgreContext();
		virtual ~OgreContext();

		static OgreContext* instance();

		// initialize the application
		void initApp(std::string appName);

		// create mRoot and initialize the strings mResourcesCfg and mPluginsCfg according to the configuration
		void createRoot();

		// lets Ogre know where to look for the resources
		void settingResources();

		// create the window, the camera and the viewport
		void createWindow(std::string appName);

		// Return a pointer to the SceneManager
		Ogre::SceneManager* getSceneManager();

		bool renderLoop();
};