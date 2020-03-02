#include "ApplicationContext.h"

//#include <OgreRoot.h>
#include <OgreException.h>
#include <OgreConfigFile.h>
#include <OgreSceneManager.h>
#include <OgreCamera.h>
//#include <OgreWindowEventUtilities.h>

#include "OgreViewport.h"
#include "OgreRenderWindow.h"

ApplicationContext::ApplicationContext() : 
	mRoot(0),
	mResourcesCfg(Ogre::BLANKSTRING),
	mPluginsCfg(Ogre::BLANKSTRING)
{
}

ApplicationContext::~ApplicationContext()
{
	delete mRoot;
}

void ApplicationContext::initApp(std::string appName)
{
	createRoot();
	settingResources();
	createWindow(appName);
}

void ApplicationContext::createRoot()
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
	mRoot = new Ogre::Root(mPluginsCfg);
}

void ApplicationContext::settingResources()
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

void ApplicationContext::createWindow(std::string appName)
{
	// create a RenderWindow instance
	Ogre::RenderSystem* rs = mRoot->getRenderSystemByName("Direct3D11 Rendering Subsystem"); // ----------------------------------------------------------- PREGUNTAR

	mRoot->setRenderSystem(rs);
	rs->setConfigOption("Full Screen", "No");
	rs->setConfigOption("Video Mode", "800 x 600 @ 32-bit colour");

	mWindow = mRoot->initialise(true, appName);

	// default number of mipmaps to be used
	//Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);
	//Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

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

	mCam->setPosition(0, 0, 1000);
	mCam->lookAt(Ogre::Vector3(0, 0, 0), Ogre::Node::TS_WORLD);

	//  declare and create the viewport
	Ogre::Viewport* vp = mWindow->addViewport(camera);
	
	vp->setBackgroundColour(Ogre::ColourValue(0, 0, 0));

	camera->setAspectRatio(Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));

	// ambient light
	//mSM->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));

	//Ogre::Light* light = mSM->createLight("MainLight");
	//light->setType(Ogre::Light::LT_DIRECTIONAL);
	//light->setDiffuseColour(0.75, 0.75, 0.75);

	//mLight = mSM->getRootSceneNode()->createChildSceneNode("mLight");
	////mLight = mCam->createChildSceneNode("nLuz");
	//mLight->attachObject(light);

	//mLight->setDirection(Ogre::Vector3(-1, -1, -1));  //vec3.normalise();
}

bool ApplicationContext::renderLoop()
{
	while (true)
	{
		//Ogre::WindowEventUtilities::messagePump();

		if (mWindow->isClosed()) 
			return false;

		if (!mRoot->renderOneFrame()) 
			return false;
	}
}
