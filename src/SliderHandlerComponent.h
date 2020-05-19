#pragma once
#include "Component.h"
#include "Factory.h"

class GuiSliderComponent;
class GuiLabelComponent;
class SpecialFloatHandlerComponent;

// FACTORY INFRASTRUCTURE DECLARATION
DECLARE_FACTORY(SliderHandlerComponent);

class SliderHandlerComponent : public Component {
    GuiSliderComponent* _slider = nullptr;
    GuiLabelComponent* _label = nullptr;
    SpecialFloatHandlerComponent* _floatHandler = nullptr;

  public:
    virtual void destroy();
    void init();
    virtual void setSlider(GuiSliderComponent* slider);
    virtual void setLabel(GuiLabelComponent* label);
    void setFloatHandler(SpecialFloatHandlerComponent* floatHandler);
    virtual void onSliderChange();
};
