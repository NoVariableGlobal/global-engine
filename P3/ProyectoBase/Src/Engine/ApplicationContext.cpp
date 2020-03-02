#include "ApplicationContext.h"

//#include <OgreRoot.h>
#include <OgreException.h>
#include <OgreConfigFile.h>
#include <OgreSceneManager.h>
#include <OgreCamera.h>

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

	// construct an instance of the root object
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
	mWindow = mRoot->initialise(true, appName);

	// default number of mipmaps to be used
	//Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);
	//Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

	// create a SceneManager instance
	mSM = mRoot->createSceneManager();

	// add a Camera member
	Ogre::Camera* mCamera;
	mCamera = mSM->createCamera("MainCam");
	mCamera->setNearClipDistance(1);
	mCamera->setFarClipDistance(10000);
	mCamera->setAutoAspectRatio(true);

	mCamNode = mSM->getRootSceneNode()->createChildSceneNode("mCam");
	mCamNode->attachObject(mCamera);

	mCamNode->setPosition(0, 0, 1000);
	mCamNode->lookAt(Ogre::Vector3(0, 0, 0), Ogre::Node::TS_WORLD);

	//  declare and create the viewport
	Ogre::Viewport* vp = mWindow->addViewport(mCamera);
	
	vp->setBackgroundColour(Ogre::ColourValue(0, 0, 0));

	mCamera->setAspectRatio(Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));
}

bool ApplicationContext::renderLoop()
{
	while (true)
	{
		if (mWindow->isClosed()) 
			return false;

		if (!mRoot->renderOneFrame()) 
			return false;
	}
}
