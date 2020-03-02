#pragma once

#include <OgreRoot.h>

#include <string>

class ApplicationContext
{
	private:
		Ogre::Root* mRoot = nullptr;
		Ogre::String mResourcesCfg;
		Ogre::String mPluginsCfg;

		Ogre::RenderWindow* mWindow = nullptr;
		Ogre::SceneManager* mSM = nullptr;
		Ogre::SceneNode* mCam = nullptr;
		Ogre::SceneNode* mLight = nullptr;

	public:
		ApplicationContext();
		virtual ~ApplicationContext();

		// initialize the application
		void initApp(std::string appName);

		// create mRoot and initialize the strings mResourcesCfg and mPluginsCfg according to the configuration
		void createRoot();
		// lets Ogre know where to look for the resources
		void settingResources();
		// create the window, the camera and the viewport
		void createWindow(std::string appName);

		bool renderLoop();
};