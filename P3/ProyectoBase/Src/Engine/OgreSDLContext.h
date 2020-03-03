#pragma once

#include <OgreRoot.h>

#include <string>

class SDL_Window;

struct NativeWindowPair
{
	Ogre::RenderWindow* render = nullptr;
	SDL_Window* native = nullptr;
};

class OgreSDLContext
{
	protected:
		Ogre::Root* mRoot = nullptr;
		Ogre::String mResourcesCfg;
		Ogre::String mPluginsCfg;

		Ogre::SceneManager* mSM = nullptr;

		NativeWindowPair mWindow;

		Ogre::SceneNode* mCam = nullptr;
		Ogre::SceneNode* mLight = nullptr;

		bool grab = false, showCursor = true;

	public:
		OgreSDLContext();
		virtual ~OgreSDLContext();

		// initialize the application
		void initApp(std::string appName);
		// create mRoot and initialize the strings mResourcesCfg and mPluginsCfg according to the configuration
		void createRoot();
		// lets Ogre know where to look for the resources
		void settingResources();
		// create the render window
		void createWindow(std::string appName);
		// keep (or not) the mouse inside the window
		void setWindowGrab(bool _grab, bool _showCursor);

		// close the application
		void closeApp();
		// cleans up and shuts down the context.
		void shutdown();

		// process all window events since last call
		void pollEvents();

		//------------------------- ESTO NO ESTARA AQUI
		void renderLoop();
};