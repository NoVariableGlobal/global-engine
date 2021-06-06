#pragma once
#include "LocaleManager.h"
#include <map>
#include <string>

class Scene;
class Loader;

class Game {
    // Save <scene name, scene file>
    std::map<std::string, std::string> scenesQueue_;
    Scene* scene_ = nullptr;

    bool exit_ = false;
    bool end_ = false;
    bool win_ = false;

    std::string sceneToChange_;
    bool sceneChange_ = false;
    bool deleteAll_ = false;

    const uint32_t frame_rate = 1000 / 60;
    uint32_t startTime;
    uint32_t lag;

    float _timestep = frame_rate / 1000.0f;

    LocaleManager localeManager_{};
    Locale locale_{localeManager_};

  public:
    Game();
    ~Game();

    // initialise OgreSDL
    void initContext();

    // initialise the game
    bool init(std::string firstScene, const std::string schemeName,
              std::string scheme, std::string mouseImage, std::string font);
    // loop of the game
    void run();
    // update the game
    void update();
    // render the entities of the game
    void render();
    // handle the input of the game
    void handleInput();

    // tells if the scene is going to be change
    void setChangeScene(bool change, std::string sceneName, bool deleteAll);
    // change the current scene
    void setScene(std::string sceneName);

    void setFullScreen();

    void quit();

    Locale& getLocale() const { return locale_; }
};
