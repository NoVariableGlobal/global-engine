#include "ChangeAndClearSceneButtonC.h"
#include "ComponentsManager.h"
#include "FactoriesFactory.h"
#include "Game.h"
#include "OgreSDLContext.h"
#include "Scene.h"
#include <CEGUI/CEGUI.h>
#include <CEGUI/Window.h>
#include <iostream>
#include <json.h>

void ChangeAndClearSceneButtonComponent::create() {
    CEGUI::Window* button =
        GuiButtonComponent::create(text, position, size, name);

    button->subscribeEvent(
        CEGUI::PushButton::EventClicked,
        CEGUI::Event::Subscriber(&ChangeAndClearSceneButtonComponent::onClick,
                                 this));
}

void ChangeAndClearSceneButtonComponent::onClick() {
    scene_->changeScene(changeScene, true);
}

void ChangeAndClearSceneButtonComponent::destroy() {
    CEGUI::WindowManager::getSingleton().destroyWindow(myself);
    setActive(false);
    scene_->getComponentsManager()->eraseDC(this);
}

// Setters

void ChangeAndClearSceneButtonComponent::setText(std::string t) { text = t; }

void ChangeAndClearSceneButtonComponent::setPosition(glm::vec2 p) {
    position = p;
}

void ChangeAndClearSceneButtonComponent::setSize(glm::vec2 s) { size = s; }

void ChangeAndClearSceneButtonComponent::setName(std::string n) { name = n; }

void ChangeAndClearSceneButtonComponent::setChangeScene(std::string s) {
    changeScene = s;
}

// FACTORY INFRASTRUCTURE DEFINITION

ChangeAndClearSceneButtonComponentFactory::
    ChangeAndClearSceneButtonComponentFactory() =
    default;

Component* ChangeAndClearSceneButtonComponentFactory::create(Entity* _father,
                                                     Json::Value& _data,
                                                     Scene* _scene) {
    ChangeAndClearSceneButtonComponent* changeAndClearSceneButtonComponent =
        new ChangeAndClearSceneButtonComponent();
    _scene->getComponentsManager()->addDC(changeAndClearSceneButtonComponent);

    changeAndClearSceneButtonComponent->setFather(_father);
    changeAndClearSceneButtonComponent->setScene(_scene);

    if (!_data["text"].isString())
        throw std::exception(
            "ChangeSceneButtonComponent: text is not a string");
    changeAndClearSceneButtonComponent->setText(_data["text"].asString());

    if (!_data["position"].isArray())
        throw std::exception(
            "ChangeSceneButtonComponent: position is not an array");
    changeAndClearSceneButtonComponent->setPosition(glm::vec2(
        _data["position"][0].asFloat(), _data["position"][1].asFloat()));

    if (!_data["size"].isArray())
        throw std::exception(
            "ChangeSceneButtonComponent: size is not an array");
    changeAndClearSceneButtonComponent->setSize(
        glm::vec2(_data["size"][0].asFloat(), _data["size"][1].asFloat()));

    if (!_data["name"].isString())
        throw std::exception(
            "ChangeSceneButtonComponent: name is not a string");
    changeAndClearSceneButtonComponent->setName(_data["name"].asString());

    if (!_data["scene"].isString())
        throw std::exception(
            "ChangeSceneButtonComponent: scene is not a string");
    changeAndClearSceneButtonComponent->setChangeScene(
        _data["scene"].asString());

    changeAndClearSceneButtonComponent->create();

    return changeAndClearSceneButtonComponent;
}

DEFINE_FACTORY(ChangeAndClearSceneButtonComponent);