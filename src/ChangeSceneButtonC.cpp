#include "ChangeSceneButtonC.h"
#include "ComponentsManager.h"
#include "FactoriesFactory.h"
#include "Game.h"
#include "OgreSDLContext.h"
#include "Scene.h"
#include <CEGUI/CEGUI.h>
#include <CEGUI/Window.h>
#include <iostream>
#include <json.h>

void ChangeSceneButtonComponent::create() {
    CEGUI::Window* button =
        GuiButtonComponent::create(text, position, size, name);

    button->subscribeEvent(
        CEGUI::PushButton::EventClicked,
        CEGUI::Event::Subscriber(&ChangeSceneButtonComponent::onClick, this));
}

void ChangeSceneButtonComponent::onClick() { scene_->changeScene(changeScene); }

void ChangeSceneButtonComponent::destroy() {
    CEGUI::WindowManager::getSingleton().destroyWindow(myself);
    setActive(false);
    scene_->getComponentsManager()->eraseDC(this);
}

// Setters

void ChangeSceneButtonComponent::setText(std::string t) { text = t; }

void ChangeSceneButtonComponent::setPosition(glm::vec2 p) { position = p; }

void ChangeSceneButtonComponent::setSize(glm::vec2 s) { size = s; }

void ChangeSceneButtonComponent::setName(std::string n) { name = n; }

void ChangeSceneButtonComponent::setChangeScene(std::string s) {
    changeScene = s;
}

// FACTORY INFRASTRUCTURE DEFINITION

ChangeSceneButtonComponentFactory::ChangeSceneButtonComponentFactory() =
    default;

Component* ChangeSceneButtonComponentFactory::create(Entity* _father,
                                                     Json::Value& _data,
                                                     Scene* _scene) {
    ChangeSceneButtonComponent* changeSceneButtonComponent =
        new ChangeSceneButtonComponent();
    _scene->getComponentsManager()->addDC(changeSceneButtonComponent);

    changeSceneButtonComponent->setFather(_father);
    changeSceneButtonComponent->setScene(_scene);

    if (!_data["text"].isString())
        throw std::exception(
            "ChangeSceneButtonComponent: text is not a string");
    auto text = _scene->getGame()->getLocale().format(_data["text"].asString());
    changeSceneButtonComponent->setText(text);

    if (!_data["position"].isArray())
        throw std::exception(
            "ChangeSceneButtonComponent: position is not an array");
    changeSceneButtonComponent->setPosition(glm::vec2(
        _data["position"][0].asFloat(), _data["position"][1].asFloat()));

    if (!_data["size"].isArray())
        throw std::exception(
            "ChangeSceneButtonComponent: size is not an array");
    changeSceneButtonComponent->setSize(
        glm::vec2(_data["size"][0].asFloat(), _data["size"][1].asFloat()));

    if (!_data["name"].isString())
        throw std::exception(
            "ChangeSceneButtonComponent: name is not a string");
    changeSceneButtonComponent->setName(_data["name"].asString());

    if (!_data["scene"].isString())
        throw std::exception(
            "ChangeSceneButtonComponent: scene is not a string");
    changeSceneButtonComponent->setChangeScene(_data["scene"].asString());

    changeSceneButtonComponent->create();

    return changeSceneButtonComponent;
}

DEFINE_FACTORY(ChangeSceneButtonComponent);