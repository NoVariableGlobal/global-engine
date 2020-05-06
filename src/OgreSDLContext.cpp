#include "OgreSDLContext.h"
#include "RTSSDefaultTechniqueListener.h"

#include <Ogre.h>

#include <SDL.h>
#include <SDL_syswm.h>
#include <iostream>

#pragma warning(disable : 4996)
#include <OgreSTBICodec.h>

#include <OgreShaderGenerator.h>

OgreSDLContext* OgreSDLContext::instance_ = nullptr;

OgreSDLContext::OgreSDLContext()
    : mResourcesCfg_(Ogre::BLANKSTRING), mPluginsCfg_(Ogre::BLANKSTRING) {}

OgreSDLContext* OgreSDLContext::getInstance() { return instance_; }

void OgreSDLContext::init() { instance_ = new OgreSDLContext(); }

void OgreSDLContext::initApp(const std::string& appName) {
    createRoot();
    createWindow(appName);
    settingResources();
    setWindowGrab(grab_, showCursor_);
    initialiseRTShaderSystem();
}

void OgreSDLContext::createRoot() {
    // define the strings that identify the resource and plugin configuration
    // files
#ifdef _DEBUG
    mResourcesCfg_ = "resources_d.cfg";
    mPluginsCfg_ = "plugins_d.cfg";
#else
    mResourcesCfg_ = "resources.cfg";
    mPluginsCfg_ = "plugins.cfg";
#endif

    // create an instance of the root object
    mRoot_ = new Ogre::Root(mPluginsCfg_, "ogre.cfg");
    Ogre::STBIImageCodec::startup();
    mRoot_->restoreConfig();
    mRoot_->initialise(false);
}

void OgreSDLContext::settingResources() const {
    // create a Ogre::ConfigFile object and use it to parse our cfg file
    Ogre::ConfigFile cf;
    cf.load(mResourcesCfg_);

    // Filesystem, Zip, etc.)

    // allow us to iterate through all of the sections discovered by the parser
    Ogre::ConfigFile::SettingsBySection_ secIt = cf.getSettingsBySection();

    // Ogre::MaterialManager::getSingleton().initialise();
    // Ogre::ParticleSystemManager::getSingleton()._createRenderer(
    // mRoot->getRenderSystem()->getName());

    // iterate through all of the results.
    for (auto it : secIt) {
        Ogre::String secName = it.first;
        // ask for another iterator that will let us iterate through the items
        // in each section
        Ogre::ConfigFile::SettingsMultiMap* settings = &it.second;
        Ogre::ConfigFile::SettingsMultiMap::iterator it2;

        // scan through each item with this iterator
        for (it2 = settings->begin(); it2 != settings->end(); ++it2) {
            // unpack each pair
            Ogre::String locType = it2->first; // location type of this resource
            Ogre::String name = it2->second;   // the path

            // add this location to our ResourceGroupManager
            Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
                name, locType, secName);
        }
    }
    Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
}

void OgreSDLContext::createWindow(const std::string& appName) {
    Ogre::ConfigOptionMap ropts = mRoot_->getRenderSystem()->getConfigOptions();

    std::istringstream mode(ropts["Video Mode"].currentValue);
    Ogre::String token;
    uint32_t w, h;
    mode >> w;     // width
    mode >> token; // 'x' as separator between width and height
    mode >> h;     // height

    std::cout << '\n' << w << " " << h << '\n';

    Ogre::NameValuePairList miscParams;

    miscParams["FSAA"] = ropts["FSAA"].currentValue;
    miscParams["vsync"] = ropts["VSync"].currentValue;
    miscParams["gamma"] = ropts["sRGB Gamma Conversion"].currentValue;

    if (!SDL_WasInit(SDL_INIT_VIDEO | SDL_INIT_TIMER))
        if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0) {
            SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
            /*EXCEPCION*/
        }

    int flags = 0;

    mWindow_.native = SDL_CreateWindow(appName.c_str(), SDL_WINDOWPOS_CENTERED,
                                       SDL_WINDOWPOS_CENTERED, w, h, flags);

    SDL_SysWMinfo wmInfo;
    SDL_VERSION(&wmInfo.version);
    SDL_GetWindowWMInfo(mWindow_.native, &wmInfo);

    miscParams["externalWindowHandle"] =
        Ogre::StringConverter::toString(size_t(wmInfo.info.win.window));

    mWindow_.render =
        mRoot_->createRenderWindow(appName, w, h, false, &miscParams);

    // create a SceneManager instance
    mSM_ = mRoot_->createSceneManager();
    if (ambientLight_)
        mSM_->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));
}

void OgreSDLContext::setWindowGrab(bool grab, const bool showCursor) {
    const auto g = SDL_bool(grab);
    SDL_SetWindowGrab(mWindow_.native, g);
    SDL_ShowCursor(showCursor);
}

void OgreSDLContext::initialiseRTShaderSystem() {
    try {
        if (Ogre::RTShader::ShaderGenerator::initialize()) {
            // Grab the shader generator pointer.
            mShaderGenerator_ =
                Ogre::RTShader::ShaderGenerator::getSingletonPtr();

            // Add the shader libs resource location.
            Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
                "media", "FileSystem");

            // Set the scene manager.
            mShaderGenerator_->addSceneManager(mSM_);

            mMaterialListener_ =
                new RTSSDefaultTechniqueListener(mShaderGenerator_);
            Ogre::MaterialManager::getSingleton().addListener(
                mMaterialListener_);
        } else {
            throw std::runtime_error("Ogre could not initialize correctly");
        }
    } catch (std::runtime_error const& runErr) {
        printf("%s \n", runErr.what());
    }
}

void OgreSDLContext::erase() {
    closeApp();
    delete instance_;
}

void OgreSDLContext::closeApp() {
    if (mRoot_ != nullptr)
        mRoot_->saveConfig();

    shutdown();

    mRoot_->destroySceneManager(mSM_);

    delete mRoot_;
    mRoot_ = nullptr;

    delete mMaterialListener_;

    Ogre::STBIImageCodec::shutdown();

    SDL_Quit();
}
void OgreSDLContext::shutdown() {
    destroyRTShaderSystem();

    if (mWindow_.render != nullptr) {
        mRoot_->destroyRenderTarget(mWindow_.render);
        mWindow_.render = nullptr;
    }

    if (mWindow_.native != nullptr) {
        SDL_DestroyWindow(mWindow_.native);
        SDL_QuitSubSystem(SDL_INIT_VIDEO | SDL_INIT_TIMER);
        mWindow_.native = nullptr;
    }
}

void OgreSDLContext::destroyRTShaderSystem() {
    // restore default scheme.
    Ogre::MaterialManager::getSingleton().setActiveScheme(
        Ogre::MaterialManager::DEFAULT_SCHEME_NAME);

    // destroy RTShader system.
    if (mShaderGenerator_ != nullptr) {
        Ogre::RTShader::ShaderGenerator::getSingleton().destroy();
        mShaderGenerator_ = nullptr;
    }
}

Ogre::RenderTarget* OgreSDLContext::getRenderTarget() const {
    return mRoot_->getRenderTarget("Test");
}

bool OgreSDLContext::pollEvents(const SDL_Event event) // from frameStarted
{
    if (mWindow_.native == nullptr)
        return exit_; // SDL events not initialized

    switch (event.type) {
    case SDL_QUIT:
        mRoot_->queueEndRendering();
        exit_ = true;
        break;

    case SDL_WINDOWEVENT:
        if (event.window.windowID == SDL_GetWindowID(mWindow_.native)) {
            if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
                Ogre::RenderWindow* win = mWindow_.render;
                win->windowMovedOrResized();
            }
        }
        break;

    default:
        break;
    }

    return exit_;
}

void OgreSDLContext::setFullScreen() {
    SDL_SetWindowFullscreen(mWindow_.native, SDL_WINDOW_FULLSCREEN);
}

Ogre::Root* OgreSDLContext::getRoot() const { return mRoot_; }

Ogre::SceneManager* OgreSDLContext::getSceneManager() const { return mSM_; }

Ogre::RenderWindow* OgreSDLContext::getRenderWindow() const {
    return mWindow_.render;
}

SDL_Window* OgreSDLContext::getSDLWindow() const { return mWindow_.native; }

void OgreSDLContext::renderLoop() const { mRoot_->renderOneFrame(); }
