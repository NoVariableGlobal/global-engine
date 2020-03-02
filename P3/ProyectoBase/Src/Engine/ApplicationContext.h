#pragma once

#ifndef __ApplicationContext_H__
#define __ApplicationContext_H__

#include <string>

#include <OgreBitesPrerequisites.h>
#include <OgreBuildSettings.h>
#include <OgreLogManager.h>
#include <OgrePlugin.h>
#include <OgreFileSystemLayer.h>

#include <OgreFrameListener.h>
#include <OgreSGTechniqueResolverListener.h>
#include <OgreInput.h>
#include <OgreOverlaySystem.h>
#include <SDL.h>

namespace OgreBites {
	typedef SDL_Window NativeWindowType;

	/**
	link between a renderwindow and a platform specific window
	*/
	struct NativeWindowPair	{
		Ogre::RenderWindow* render = nullptr;
		NativeWindowType* native = nullptr;
	};

	/**
	Base class responsible for setting up a common context for applications.
	Subclass to implement specific event callbacks.
	*/
	class ApplicationContext : public Ogre::FrameListener {
	public:
		explicit ApplicationContext(const Ogre::String& appName = OGRE_VERSION_NAME);

		virtual ~ApplicationContext();
		
		Ogre::RenderWindow* getRenderWindow() const;

		Ogre::Root* getRoot();

		//Ogre::OverlaySystem* getOverlaySystem() const;

		void initApp();

		void closeApp();

		virtual bool frameStarted(const Ogre::FrameEvent& evt);
		virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);
		virtual bool frameEnded(const Ogre::FrameEvent& evt);
		virtual void windowMoved(Ogre::RenderWindow* rw);
		virtual void windowResized(Ogre::RenderWindow* rw);
		virtual bool windowClosing(Ogre::RenderWindow* rw);
		virtual void windowClosed(Ogre::RenderWindow* rw);
		virtual void windowFocusChange(Ogre::RenderWindow* rw);

		//void _fireInputEvent(const Event& event) const;

		bool initialiseRTShaderSystem();

		void destroyRTShaderSystem();

		virtual void setup();

		virtual void createRoot();

		virtual bool oneTimeConfig();

		void setWindowGrab(bool grab);  

		virtual void locateResources();

		virtual void loadResources();

		virtual void shutdown();

		void pollEvents();

		void addInputListener(InputListener* lis);

		void removeInputListener(InputListener* lis);

		virtual NativeWindowPair createWindow(const Ogre::String& name);

	protected:
		Ogre::Root* mRoot;                                  // OGRE root
		//NativeWindowPair mWindow;                           // the window

		Ogre::FileSystemLayer* mFSLayer;                    // File system abstraction layer
		Ogre::OverlaySystem* mOverlaySystem;                // Overlay system
		
		std::set<InputListener*> mInputListeners;

		bool mFirstRun;
		Ogre::String mAppName;
		Ogre::String mSolutionPath;                         // Variable para hacer las rutas relativas al directorio de la solución
		
		Ogre::String mRTShaderLibPath;
		Ogre::RTShader::ShaderGenerator * mShaderGenerator; // The Shader generator instance.
		SGTechniqueResolverListener * mMaterialMgrListener; // Shader generator material manager listener.

	};
}

#endif