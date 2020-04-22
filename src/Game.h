#pragma once
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

    //GuiComponent* mGui_;

  public:
    Game();
    ~Game();

    // initialise OgreSDL
    void initContext();

    // initialise the game
    bool init(std::string firstScene);
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

    void quit();
};
