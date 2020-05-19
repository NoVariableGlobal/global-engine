#include "GuiSliderC.h"
#include "ComponentsManager.h"
#include "Scene.h"
#include <CEGUI/WindowManager.h>
#include <json.h>

#include "Entity.h"
#include "FactoriesFactory.h"
#include <CEGUI/CEGUI.h>
#include <CEGUI/SubscriberSlot.h>
#include <CEGUI/widgets/Slider.h>
#include <CEGUI\Window.h>
#include <iostream>

#include "GuiContext.h"
#include "SliderHandlerComponent.h"

CEGUI::Slider* GuiSliderComponent::create(const glm::vec2 position,
                                          const glm::vec2 size,
                                          const std::string& name) {
    myself = dynamic_cast<CEGUI::Slider*>(
        GuiContext::getInstance()->createSlider(position, size, name));
    myself->setCurrentValue(1.0f);
    return myself;
}

void GuiSliderComponent::subscribeEvent(const CEGUI::String& event,
                                        CEGUI::SubscriberSlot subscriber) {

    myself->subscribeEvent(event, subscriber);
}

float GuiSliderComponent::getValue() { return myself->getCurrentValue(); }

void GuiSliderComponent::destroy() {
    CEGUI::WindowManager::getSingleton().destroyWindow(myself);
    setActive(false);
    scene_->getComponentsManager()->eraseDC(this);
}

// FACTORY INFRASTRUCTURE DEFINITION

GuiSliderComponentFactory::GuiSliderComponentFactory() = default;

Component* GuiSliderComponentFactory::create(Entity* _father,
                                             Json::Value& _data,
                                             Scene* _scene) {
    GuiSliderComponent* guiSliderComponent = new GuiSliderComponent();
    _scene->getComponentsManager()->addDC(guiSliderComponent);

    guiSliderComponent->setFather(_father);
    guiSliderComponent->setScene(_scene);

    if (!_data["position"].isArray())
        throw std::exception("QuitButtonComponent: position is not an array");

    if (!_data["size"].isArray())
        throw std::exception("QuitButtonComponent: size is not an array");

    if (!_data["name"].isString())
        throw std::exception("QuitButtonComponent: name is not a string");

    guiSliderComponent->create(
        glm::vec2(_data["position"][0].asFloat(),
                  _data["position"][1].asFloat()),
        glm::vec2(_data["size"][0].asFloat(), _data["size"][1].asFloat()),
        _data["name"].asString());

    return guiSliderComponent;
}

DEFINE_FACTORY(GuiSliderComponent);
