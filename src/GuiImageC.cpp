#include "GuiImageC.h"
#include "ComponentsManager.h"
#include "Entity.h"
#include "FactoriesFactory.h"
#include "GuiContext.h"
#include "OgreSDLContext.h"
#include "Scene.h"
#include <CEGUI/CEGUI.h>
#include <CEGUI\Window.h>
#include <iostream>
#include <json.h>

void GuiImageComponent::create() {
    myself =
        GuiContext::getInstance()->createImage(image, position, size, name);
}

void GuiImageComponent::destroy() {
    CEGUI::WindowManager::getSingleton().destroyWindow(myself);
    setActive(false);
    scene_->getComponentsManager()->eraseDC(this);
}

CEGUI::Window GuiImageComponent::getWindow() { return myself; }

// Setters

void GuiImageComponent::setImage(std::string t) { image = t; }

void GuiImageComponent::setPosition(glm::vec2 p) { position = p; }

void GuiImageComponent::setSize(glm::vec2 s) { size = s; }

void GuiImageComponent::setName(std::string n) { name = n; }

// FACTORY INFRASTRUCTURE DEFINITION

GuiImageComponentFactory::GuiImageComponentFactory() = default;

Component* GuiImageComponentFactory::create(Entity* _father, Json::Value& _data,
                                            Scene* _scene) {
    GuiImageComponent* guiImageComponent = new GuiImageComponent();
    _scene->getComponentsManager()->addDC(guiImageComponent);

    guiImageComponent->setFather(_father);
    guiImageComponent->setScene(_scene);

    if (!_data["image"].isString())
        throw std::exception("GuiImageComponent: image is not a string");
    guiImageComponent->setImage(_data["image"].asString());

    if (!_data["position"].isArray())
        throw std::exception("GuiImageComponent: position is not an array");
    guiImageComponent->setPosition(glm::vec2(_data["position"][0].asFloat(),
                                             _data["position"][1].asFloat()));

    if (!_data["size"].isArray())
        throw std::exception("GuiImageComponent: size is not an array");
    guiImageComponent->setSize(
        glm::vec2(_data["size"][0].asFloat(), _data["size"][1].asFloat()));

    if (!_data["name"].isString())
        throw std::exception("GuiImageComponent: name is not a string");
    guiImageComponent->setName(_data["name"].asString());

    guiImageComponent->create();

    return guiImageComponent;
}

DEFINE_FACTORY(GuiImageComponent);