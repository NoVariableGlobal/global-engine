#include "TestChangeSceneIC.h"
#include "ComponentsManager.h"
#include "FactoriesFactory.h"
#include "Factory.h"
#include "Scene.h"

#include "OgreRoot.h"

#include <json.h>

#include <iostream>

TestChangeSceneIC::TestChangeSceneIC() {}

TestChangeSceneIC::~TestChangeSceneIC() {}

void TestChangeSceneIC::setSceneToChange(std::string scene) {
    sceneToChange = scene;
}

void TestChangeSceneIC::handleInput(const SDL_Event& _event) {
    if (_event.type == SDL_KEYDOWN) {
        if (_event.key.keysym.sym == SDLK_SPACE)
            scene->changeScene(sceneToChange);
    }
}

// FACTORY INFRASTRUCTURE
class TestChangeSceneICFactory final : public ComponentFactory {
  public:
    TestChangeSceneICFactory() = default;

    Component* create(Entity* _father, Json::Value& _data,
                      Scene* _scene) override {
        TestChangeSceneIC* change = new TestChangeSceneIC();
        _scene->getComponentsManager()->addIC(change);

        change->setFather(_father);
        change->setScene(_scene);

        if (!_data["sceneToChange"].isString())
            throw std::exception(
                "TestChangeSceneIC: sceneToChange is not a string.");
        change->setSceneToChange(_data["sceneToChange"].asString());

        return change;
    };
};

REGISTER_FACTORY("TestChangeSceneIC", TestChangeSceneIC);
