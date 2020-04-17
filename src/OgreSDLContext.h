#pragma once

#include <string>

#include <SDL_events.h>

class RTSSDefaultTechniqueListener;

namespace Ogre {
    class RenderWindow;
    class RenderTarget;
    class Root;
    class Viewport;
    class SceneManager;
    class SceneNode;

    typedef std::string _StringBase;
    typedef _StringBase String;

    namespace RTShader {
        class ShaderGenerator;
    }
} // namespace Ogre

struct NativeWindowPair {
    Ogre::RenderWindow* render = nullptr;
    SDL_Window* native = nullptr;
};

class OgreSDLContext {
  private:
    static OgreSDLContext* _instance;

    Ogre::Root* mRoot = nullptr;
    Ogre::String mResourcesCfg;
    Ogre::String mPluginsCfg;

    Ogre::SceneManager* mSM = nullptr;

    NativeWindowPair mWindow;

    Ogre::String mRTShaderLibPath;
    Ogre::RTShader::ShaderGenerator* mShaderGenerator =
        nullptr; // The Shader generator instance.
    RTSSDefaultTechniqueListener* mMaterialListener =
        nullptr; // Shader generator material manager listener.

    bool grab = false, showCursor = true, ambientLight = false;

    bool exit = false;

    OgreSDLContext();

  public:
    static OgreSDLContext* getInstance();
    static void init();

    void erase();

    // initialize the application
    void initApp(std::string appName);
    // create mRoot and initialize the strings mResourcesCfg and mPluginsCfg
    // according to the configuration
    void createRoot();
    // lets Ogre know where to look for the resources
    void settingResources();
    // create the render window
    void createWindow(std::string appName);
    // keep (or not) the mouse inside the window
    void setWindowGrab(bool _grab, bool _showCursor);
    // initialize the RT Shader system.
    void initialiseRTShaderSystem();

    // close the application
    void closeApp();
    // cleans up and shuts down the context.
    void shutdown();
    // destroy the RT Shader system.
    void destroyRTShaderSystem();

    // return a pointer to the OgreRoot
    Ogre::Root* getOgreRoot();
    // return a pointer to the RenderTarget
    Ogre::RenderTarget* getRenderTarget();
    // return a pointer to the SceneManager
    Ogre::SceneManager* getSceneManager();
    // return a pointer to the RenderWindow
    Ogre::RenderWindow* getRenderWindow();
    // return a pointer to the SDLWindow
    SDL_Window* getSDLWindow();
    // process all window events since last call
    bool pollEvents(SDL_Event event);

    void renderLoop();
};