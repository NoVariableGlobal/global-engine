#include "OgreSDLContext.h"

#include <OgreRoot.h>
#include <OgreException.h>
#include <OgreConfigFile.h>
#include <OgreSceneManager.h>
#include <OgreCamera.h>
#include <OgreMaterialManager.h>
#include <OgreShaderGenerator.h>

#include <SDL.h>
#include <SDL_syswm.h>

#include <iostream>

#include "OgreViewport.h"
#include "OgreRenderWindow.h"
#include "OgreEntity.h"
#include "RTSSDefaultTechniqueListener.h"


OgreSDLContext* OgreSDLContext::_instance = nullptr;

OgreSDLContext::OgreSDLContext() :
	mRoot(0), mResourcesCfg(Ogre::BLANKSTRING), mPluginsCfg(Ogre::BLANKSTRING)
{
}

void OgreSDLContext::erase()
{
	closeApp();
	delete _instance;
}

void OgreSDLContext::closeApp()
{
	if (mRoot != nullptr)
		mRoot->saveConfig();

	shutdown();

	mRoot->destroySceneManager(mSM);

	delete mRoot;
	mRoot = nullptr;

	if (mMaterialListener != nullptr)
		delete mMaterialListener;

	//Ogre::FreeImageCodec::shutdown();
}

void OgreSDLContext::shutdown()
{
	destroyRTShaderSystem();

	if (mWindow.render != nullptr)
	{
		mRoot->destroyRenderTarget(mWindow.render);
		mWindow.render = nullptr;
	}

	if (mWindow.native != nullptr)
	{
		SDL_DestroyWindow(mWindow.native);
		SDL_QuitSubSystem(SDL_INIT_VIDEO);
		mWindow.native = nullptr;
	}
}

void OgreSDLContext::destroyRTShaderSystem()
{
	// restore default scheme.
	Ogre::MaterialManager::getSingleton().setActiveScheme(Ogre::MaterialManager::DEFAULT_SCHEME_NAME);

	// destroy RTShader system.
	if (mShaderGenerator != nullptr)
	{
		Ogre::RTShader::ShaderGenerator::getSingleton().destroy();
		mShaderGenerator = nullptr;
	}
}

OgreSDLContext* OgreSDLContext::getInstance()
{
	if (_instance == nullptr) _instance = new OgreSDLContext();
	return _instance;
}


void OgreSDLContext::initApp(std::string appName)
{
	createRoot();
	settingResources();
	createWindow(appName);
	setWindowGrab(grab, showCursor);
	initialiseRTShaderSystem();
}

void OgreSDLContext::createRoot()
{
	// define the strings that identify the resource and plugin configuration files
#ifdef _DEBUG
	mResourcesCfg = "resources_d.cfg";
	mPluginsCfg = "plugins_d.cfg";
#else
	mResourcesCfg = "resources.cfg";
	mPluginsCfg = "plugins.cfg";
#endif

	// create an instance of the root object
	mRoot = new Ogre::Root(mPluginsCfg, "ogre.cfg");
	//Ogre::FreeImageCodec::startup();
	mRoot->restoreConfig();
	mRoot->initialise(false);
}

void OgreSDLContext::settingResources()
{
	// create a Ogre::ConfigFile object and use it to parse our cfg file
	Ogre::ConfigFile cf;
	cf.load(mResourcesCfg);

	// use to gather information from the parsed config file
	Ogre::String name; // path to the resources (i.e. "../media")
	Ogre::String locType; // defines what kind of location this is (i.e. Filesystem, Zip, etc.)

	// allow us to iterate through all of the sections discovered by the parser
	Ogre::ConfigFile::SettingsBySection_ secIt = cf.getSettingsBySection();

	// iterate through all of the results.
	for (auto it : secIt)
	{
		Ogre::String secName = it.first;
		// ask for another iterator that will let us iterate through the items in each section
		Ogre::ConfigFile::SettingsMultiMap* settings = &it.second;
		Ogre::ConfigFile::SettingsMultiMap::iterator it2;

		// scan through each item with this iterator
		for (it2 = settings->begin(); it2 != settings->end(); ++it2)
		{
			// unpack each pair
			locType = it2->first; // location type of this resource
			name = it2->second; // the path

			// add this location to our ResourceGroupManager
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(name, locType, secName);
		}
	}
	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
}

void OgreSDLContext::createWindow(std::string appName)
{
	Ogre::ConfigOptionMap ropts = mRoot->getRenderSystem()->getConfigOptions();

	std::istringstream mode(ropts["Video Mode"].currentValue);
	Ogre::String token;
	uint32_t w, h;
	mode >> w; // width
	mode >> token; // 'x' as seperator between width and height
	mode >> h; // height

	std::cout << '\n' << w << " " << h << '\n';

	Ogre::NameValuePairList miscParams;

	miscParams["FSAA"] = ropts["FSAA"].currentValue;
	miscParams["vsync"] = ropts["VSync"].currentValue;
	miscParams["gamma"] = ropts["sRGB Gamma Conversion"].currentValue;

	if (!SDL_WasInit(SDL_INIT_VIDEO)) SDL_InitSubSystem(SDL_INIT_VIDEO);

	int flags = SDL_WINDOW_RESIZABLE;
	if (ropts["Full Screen"].currentValue == "Yes")
		flags = SDL_WINDOW_FULLSCREEN;

	mWindow.native = SDL_CreateWindow(appName.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, flags);

	SDL_SysWMinfo wmInfo;
	SDL_VERSION(&wmInfo.version);
	SDL_GetWindowWMInfo(mWindow.native, &wmInfo);

	miscParams["externalWindowHandle"] = Ogre::StringConverter::toString(size_t(wmInfo.info.win.window));

	mWindow.render = mRoot->createRenderWindow(appName, w, h, false, &miscParams);


	// create a SceneManager instance
	mSM = mRoot->createSceneManager();
	if(ambientLight)
		mSM->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));
}

void OgreSDLContext::setWindowGrab(bool _grab, bool _showCursor)
{
	SDL_bool g = SDL_bool(_grab);
	SDL_SetWindowGrab(mWindow.native, g);
	SDL_ShowCursor(_showCursor);
}

void OgreSDLContext::initialiseRTShaderSystem()
{
	if (Ogre::RTShader::ShaderGenerator::initialize())
	{
		// Grab the shader generator pointer.
		mShaderGenerator = Ogre::RTShader::ShaderGenerator::getSingletonPtr();

		// Add the shader libs resource location.
		Ogre::ResourceGroupManager::getSingleton().addResourceLocation("media", "FileSystem");

		// Set the scene manager.
		mShaderGenerator->addSceneManager(mSM);

		mMaterialListener = new RTSSDefaultTechniqueListener(mShaderGenerator);
		Ogre::MaterialManager::getSingleton().addListener(mMaterialListener);
	}
	else
	{
		// LANZAR EXCEPCION
	}
}

void OgreSDLContext::pollEvents()   // from frameStarted
{
	if (mWindow.native == nullptr)
		return;  // SDL events not initialized

	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_QUIT:
				mRoot->queueEndRendering();
				exit = true;
				break;

			case SDL_WINDOWEVENT:
				if (event.window.windowID == SDL_GetWindowID(mWindow.native)) 
				{
					if (event.window.event == SDL_WINDOWEVENT_RESIZED)
					{
						Ogre::RenderWindow* win = mWindow.render;
						//win->resize(event.window.data1, event.window.data2);  // IG2: ERROR 
						win->windowMovedOrResized();
					}
				}
				break;

			default:
				break;
		}
	}
}

Ogre::SceneManager* OgreSDLContext::getSceneManager()
{
	return mSM;
}

Ogre::RenderWindow* OgreSDLContext::getRenderWindow()
{
	return mWindow.render;
}

bool OgreSDLContext::renderLoop()
{
	mRoot->renderOneFrame();
	pollEvents();
	return exit;
}
