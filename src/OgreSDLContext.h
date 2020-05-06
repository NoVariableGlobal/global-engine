#pragma once

#include <SDL_events.h>
#include <string>

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
    static OgreSDLContext* instance_;

    Ogre::Root* mRoot_ = nullptr;
    Ogre::String mResourcesCfg_;
    Ogre::String mPluginsCfg_;

    Ogre::SceneManager* mSM_ = nullptr;

    NativeWindowPair mWindow_;

    Ogre::String mRTShaderLibPath_;

    // The Shader generator instance.
    Ogre::RTShader::ShaderGenerator* mShaderGenerator_ = nullptr;

    // Shader generator material manager listener.
    RTSSDefaultTechniqueListener* mMaterialListener_ = nullptr;

    bool grab_ = false;
    bool showCursor_ = false;
    bool ambientLight_ = false;

    bool exit_ = false;

    OgreSDLContext();

  public:
    static OgreSDLContext* getInstance();
    static void init();

    void erase();

    // initialize the application
    void initApp(const std::string& appName);
    // create mRoot and initialize the strings mResourcesCfg and mPluginsCfg
    // according to the configuration
    void createRoot();
    // lets Ogre know where to look for the resources
    void settingResources() const;
    // create the render window
    void createWindow(const std::string& appName);
    // keep (or not) the mouse inside the window
    void setWindowGrab(bool grab, bool showCursor);
    // initialize the RT Shader system.
    void initialiseRTShaderSystem();

    // close the application
    void closeApp();
    // cleans up and shuts down the context.
    void shutdown();
    // destroy the RT Shader system.
    void destroyRTShaderSystem();

    // return a pointer to the OgreRoot
    Ogre::Root* getRoot() const;
    // return a pointer to the RenderTarget
    Ogre::RenderTarget* getRenderTarget() const;
    // return a pointer to the SceneManager
    Ogre::SceneManager* getSceneManager() const;
    // return a pointer to the RenderWindow
    Ogre::RenderWindow* getRenderWindow() const;
    // return a pointer to the SDLWindow
    SDL_Window* getSDLWindow() const;
    // process all window events since last call
    bool pollEvents(SDL_Event event);

    void setFullScreen();

    void renderLoop() const;
};