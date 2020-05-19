#include "SliderHandlerComponent.h"
#include "FactoriesFactory.h"
#include "Scene.h"
#include "ComponentsManager.h"
#include <CEGUI\Event.h>
#include <CEGUI\widgets/Slider.h>
#include <json.h>
#include "Entity.h"
#include "GuiSliderC.h"
#include "GuiLabelC.h"
#include "SpecialFloatHandlerC.h"

void SliderHandlerComponent::destroy() {
    scene_->getComponentsManager()->eraseDC(this);
}

void SliderHandlerComponent::init() {
    _slider->subscribeEvent(CEGUI::Slider::EventValueChanged, 
        CEGUI::Event::Subscriber(&SliderHandlerComponent::onSliderChange, this));
    _label->changeText("100%");
}

void SliderHandlerComponent::setSlider(GuiSliderComponent* slider) {
    _slider = slider;
}

void SliderHandlerComponent::setLabel(GuiLabelComponent* label) {
    _label = label;
}

void SliderHandlerComponent::setFloatHandler(
    SpecialFloatHandlerComponent* floatHandler) {
    _floatHandler = floatHandler;
}

void SliderHandlerComponent::onSliderChange() {
    float currentValue = _slider->getValue();
    int percentage = (int)(currentValue * 100);
    _label->changeText(std::to_string(percentage) + "%");
    _floatHandler->updateFloat(currentValue);
}

// FACTORY INFRASTRUCTURE DEFINITION

SliderHandlerComponentFactory::SliderHandlerComponentFactory() = default;

Component* SliderHandlerComponentFactory::create(Entity* _father,
                                                 Json::Value& _data,
                                            Scene* _scene) {
    SliderHandlerComponent* sliderHandlerComponent = new SliderHandlerComponent();
    _scene->getComponentsManager()->addDC(sliderHandlerComponent);

    
    if (!_data["floatHandler"].isString())
        throw std::exception("SliderHandlerComponent: floatHandler is not an string");

    sliderHandlerComponent->setFather(_father);
    sliderHandlerComponent->setScene(_scene);
    auto slider = dynamic_cast<GuiSliderComponent*>(_father->getComponent("GuiSliderComponent"));
    sliderHandlerComponent->setSlider(slider);
    auto label = dynamic_cast<GuiLabelComponent*>(
        _father->getComponent("GuiLabelComponent"));
    sliderHandlerComponent->setLabel(label);
    
    sliderHandlerComponent
        ->setFloatHandler(
            dynamic_cast<SpecialFloatHandlerComponent*>(_father->findComponent(_data["floatHandler"].asString())));

    sliderHandlerComponent->init();
    

    return sliderHandlerComponent;
}

DEFINE_FACTORY(SliderHandlerComponent);

