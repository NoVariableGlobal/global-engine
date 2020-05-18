#pragma once
#include "Component.h"
#include "Factory.h"

class GuiSliderComponent;
class GuiLabelComponent;

// FACTORY INFRASTRUCTURE DECLARATION
DECLARE_FACTORY(SliderHandlerComponent);

class SliderHandlerComponent : public Component {
    GuiSliderComponent* _slider = nullptr;
    GuiLabelComponent* _label = nullptr;

  public:
    virtual void destroy();
  void init();
  virtual void setSlider(GuiSliderComponent* slider);
    virtual void setLabel(GuiLabelComponent* label);
    virtual void onSliderChange();
};
