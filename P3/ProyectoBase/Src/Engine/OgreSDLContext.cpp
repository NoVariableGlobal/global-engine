#include "OgreSDLContext.h"

//#include <OgreRoot.h>
#include <OgreException.h>
#include <OgreConfigFile.h>
#include <OgreSceneManager.h>
#include <OgreCamera.h>

#include <SDL.h>
#include <SDL_syswm.h>

#include <iostream>

#include "OgreViewport.h"
#include "OgreRenderWindow.h"
#include "OgreEntity.h"

OgreSDLContext::OgreSDLContext() :
	mRoot(0), mResourcesCfg(Ogre::BLANKSTRING), mPluginsCfg(Ogre::BLANKSTRING)
{
}

OgreSDLContext::~OgreSDLContext()
{
	closeApp();
}

void OgreSDLContext::initApp(std::string appName)
{
	createRoot();
	settingResources();
	createWindow(appName);
	setWindowGrab(grab, showCursor);
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
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(name, locType);
		}
	}
}

void OgreSDLContext::createWindow(std::string appName)
{
	//// create a RenderWindow instance

	Ogre::RenderSystem* rs = mRoot->getRenderSystemByName("OpenGL Rendering Subsystem");
	mRoot->setRenderSystem(rs);
	mRoot->initialise(false);
	
	//----------------------------------------------------------------------------------------------PREGUNTAR CONFIGOPTIONS AL PROFESOR

	uint32_t w, h;

	Ogre::ConfigOptionMap ropts = mRoot->getRenderSystem()->getConfigOptions();

	std::istringstream mode(ropts["Video Mode"].currentValue);
	Ogre::String token;
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


	//---------------------------------------------------------------------------------------------------- MIRAR PARA CAMERA, RENDERCOMPONENT....


	// create a SceneManager instance
	mSM = mRoot->createSceneManager();

	// add a Camera member
	Ogre::Camera* camera;
	camera = mSM->createCamera("MainCam");
	camera->setNearClipDistance(1);
	camera->setFarClipDistance(10000);
	camera->setAutoAspectRatio(true);

	mCam = mSM->getRootSceneNode()->createChildSceneNode("mCam");
	mCam->attachObject(camera);

	mCam->setPosition(0, 0, 300);
	mCam->lookAt(Ogre::Vector3(0, 0, 0), Ogre::Node::TS_WORLD);

	//  declare and create the viewport
	Ogre::Viewport* vp = mWindow.render->addViewport(camera);
	
	vp->setBackgroundColour(Ogre::ColourValue(0, 0, 0));

	camera->setAspectRatio(Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));

	// ambient light
	mSM->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));

	Ogre::Light* light = mSM->createLight("MainLight");
	light->setType(Ogre::Light::LT_DIRECTIONAL);
	light->setDiffuseColour(0.75, 0.75, 0.75);

	mLight = mSM->getRootSceneNode()->createChildSceneNode("mLight");
	//mLight = mCam->createChildSceneNode("nLuz");
	mLight->attachObject(light);

	mLight->setDirection(Ogre::Vector3(-1, -1, -1));  //vec3.normalise();

	// SIMBAD
	Ogre::Entity* ent = mSM->createEntity("Sinbad.mesh");
	Ogre::SceneNode* mSinbadNode = mSM->getRootSceneNode()->createChildSceneNode("nSinbad");
	mSinbadNode->attachObject(ent);
	mSinbadNode->setScale(20, 20, 20);
}

void OgreSDLContext::setWindowGrab(bool _grab, bool _showCursor)
{
	SDL_bool g = SDL_bool(_grab);
	SDL_SetWindowGrab(mWindow.native, g);
	SDL_ShowCursor(_showCursor);
}

void OgreSDLContext::closeApp()
{
	if (mRoot != nullptr)
		mRoot->saveConfig();

	shutdown();

	mRoot->destroySceneManager(mSM);

	delete mRoot;
	mRoot = nullptr;
}

void OgreSDLContext::shutdown()
{
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
				mWindow.render->destroy();
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

void OgreSDLContext::renderLoop()
{
	while (!mWindow.render->isClosed())
	{
		mRoot->renderOneFrame();

		pollEvents();
	}

}
