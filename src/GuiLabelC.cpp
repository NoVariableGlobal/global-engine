#include "GuiLabelC.h"
#include "ComponentsManager.h"
#include "Entity.h"
#include "FactoriesFactory.h"
#include "GUI.h"
#include "OgreSDLContext.h"
#include "Scene.h"
#include <CEGUI/CEGUI.h>
#include <CEGUI\Window.h>
#include <iostream>
#include <json.h>

void GuiLabelComponent::create() {
    static_cast<GuiComponent*>(father_->getComponent("GuiComponent"))
        ->createLabel(text, position, size, name);
}

void GuiLabelComponent::destroy() {
    setActive(false);
    scene_->getComponentsManager()->eraseDC(this);
}

// Setters

void GuiLabelComponent::setText(std::string t) { text = t; }

void GuiLabelComponent::setPosition(glm::vec2 p) { position = p; }

void GuiLabelComponent::setSize(glm::vec2 s) { size = s; }

void GuiLabelComponent::setName(std::string n) { name = n; }

// FACTORY INFRASTRUCTURE DEFINITION

GuiLabelComponentFactory::GuiLabelComponentFactory() = default;

Component* GuiLabelComponentFactory::create(Entity* _father, Json::Value& _data,
                                            Scene* _scene) {
    GuiLabelComponent* guiLabelComponent = new GuiLabelComponent();
    _scene->getComponentsManager()->addDC(guiLabelComponent);

    guiLabelComponent->setFather(_father);
    guiLabelComponent->setScene(_scene);

    if (!_data["text"].isString())
        throw std::exception("QuitButtonComponent: text is not a string");
    guiLabelComponent->setText(_data["text"].asString());

    if (!_data["position"].isArray())
        throw std::exception("QuitButtonComponent: position is not an array");
    guiLabelComponent->setPosition(glm::vec2(_data["position"][0].asFloat(),
                                             _data["position"][1].asFloat()));

    if (!_data["size"].isArray())
        throw std::exception("QuitButtonComponent: size is not an array");
    guiLabelComponent->setSize(
        glm::vec2(_data["size"][0].asFloat(), _data["size"][1].asFloat()));

    if (!_data["name"].isString())
        throw std::exception("QuitButtonComponent: name is not a string");
    guiLabelComponent->setName(_data["name"].asString());

    guiLabelComponent->create();

    return guiLabelComponent;
}

DEFINE_FACTORY(GuiLabelComponent);