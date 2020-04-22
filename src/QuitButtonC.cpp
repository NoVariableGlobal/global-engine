#include "QuitButtonC.h"
#include "ComponentsManager.h"
#include "FactoriesFactory.h"
#include "Game.h"
#include "OgreSDLContext.h"
#include "Scene.h"
#include <CEGUI/CEGUI.h>
#include <CEGUI/Window.h>
#include <iostream>
#include <json.h>

void QuitButtonComponent::create() {
    CEGUI::Window* button =
        GuiButtonComponent::create(text, position, size, name);

    button->subscribeEvent(
        CEGUI::PushButton::EventClicked,
        CEGUI::Event::Subscriber(&QuitButtonComponent::onClick, this));
}

void QuitButtonComponent::onClick() {
    scene_->getGame()->quit();
    std::cout << "It just works\n";
}

void QuitButtonComponent::destroy() {
    setActive(false);
    scene_->getComponentsManager()->eraseDC(this);
}

// Setters

void QuitButtonComponent::setText(std::string t) { text = t; }

void QuitButtonComponent::setPosition(glm::vec2 p) { position = p; }

void QuitButtonComponent::setSize(glm::vec2 s) { size = s; }

void QuitButtonComponent::setName(std::string n) { name = n; }

// FACTORY INFRASTRUCTURE DEFINITION

QuitButtonComponentFactory::QuitButtonComponentFactory() = default;

Component* QuitButtonComponentFactory::create(Entity* _father,
                                              Json::Value& _data,
                                              Scene* _scene) {
    QuitButtonComponent* quitButtonComponent = new QuitButtonComponent();
    _scene->getComponentsManager()->addDC(quitButtonComponent);

    quitButtonComponent->setFather(_father);
    quitButtonComponent->setScene(_scene);

    if (!_data["text"].isString())
        throw std::exception("QuitButtonComponent: text is not a string");
    quitButtonComponent->setText(_data["text"].asString());

    if (!_data["position"].isArray())
        throw std::exception("QuitButtonComponent: position is not an array");
    quitButtonComponent->setPosition(glm::vec2(_data["position"][0].asFloat(),
                                               _data["position"][1].asFloat()));

    if (!_data["size"].isArray())
        throw std::exception("QuitButtonComponent: size is not an array");
    quitButtonComponent->setSize(
        glm::vec2(_data["size"][0].asFloat(), _data["size"][1].asFloat()));

    if (!_data["name"].isString())
        throw std::exception("QuitButtonComponent: name is not a string");
    quitButtonComponent->setName(_data["name"].asString());

    quitButtonComponent->create();

    return quitButtonComponent;
}

DEFINE_FACTORY(QuitButtonComponent);