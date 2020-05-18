#include "GuiBarComponent.h"
#include <json.h>
#include "Scene.h"
#include "ComponentsManager.h"
#include <CEGUI/WindowManager.h>

#include "Entity.h"
#include "FactoriesFactory.h"
#include <CEGUI/CEGUI.h>
#include <CEGUI\Window.h>
#include <iostream>
#include <CEGUI/widgets/Slider.h>
#include <CEGUI/SubscriberSlot.h>

#include "GuiContext.h"
#include "SliderHandlerComponent.h"

CEGUI::Slider* GuiBarComponent::create(const std::string& text,
                                       const glm::vec2 position, const glm::vec2 size,
                                       const std::string& name) {
    myself = dynamic_cast<CEGUI::Slider*>(
        GuiContext::getInstance()->createBar(text, position, size, name));
    myself->setCurrentValue(1.0f);
    return myself;
}

void GuiBarComponent::subscribeEvent(const CEGUI::String& event,
                                     CEGUI::SubscriberSlot subscriber) {

    myself->subscribeEvent(
        event,
        subscriber);
}

float GuiBarComponent::getValue() { return myself->getCurrentValue(); }

void GuiBarComponent::destroy() {
    CEGUI::WindowManager::getSingleton().destroyWindow(myself);
    setActive(false);
    scene_->getComponentsManager()->eraseDC(this);
}

// FACTORY INFRASTRUCTURE DEFINITION

GuiBarComponentFactory::GuiBarComponentFactory() = default;

Component* GuiBarComponentFactory::create(Entity* _father, Json::Value& _data,
                                          Scene* _scene) {
    GuiBarComponent* guiBarComponent = new GuiBarComponent();
    _scene->getComponentsManager()->addDC(guiBarComponent);

    guiBarComponent->setFather(_father);
    guiBarComponent->setScene(_scene);

    if (!_data["text"].isString())
        throw std::exception("QuitButtonComponent: text is not a string");
    // guiBarComponent->setText(_data["text"].asString());

    if (!_data["position"].isArray())
        throw std::exception("QuitButtonComponent: position is not an array");
    // guiBarComponent->setPosition(glm::vec2(_data["position"][0].asFloat(),
    // _data["position"][1].asFloat()));

    if (!_data["size"].isArray())
        throw std::exception("QuitButtonComponent: size is not an array");
    // guiBarComponent->setSize(glm::vec2(_data["size"][0].asFloat(),
    // _data["size"][1].asFloat()));

    if (!_data["name"].isString())
        throw std::exception("QuitButtonComponent: name is not a string");
    // guiBarComponent->setName(_data["name"].asString());

    guiBarComponent->create(
        _data["text"].asString(),
        glm::vec2(_data["position"][0].asFloat(),
                  _data["position"][1].asFloat()),
        glm::vec2(_data["size"][0].asFloat(), _data["size"][1].asFloat()),
        _data["name"].asString());

    return guiBarComponent;
}

DEFINE_FACTORY(GuiBarComponent);
