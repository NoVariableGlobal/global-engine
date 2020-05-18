#pragma once
#include "Component.h"
#include "Factory.h"

class GuiBarComponent;
class GuiLabelComponent;

// FACTORY INFRASTRUCTURE DECLARATION
DECLARE_FACTORY(SliderHandlerComponent);

class SliderHandlerComponent : public Component {
    GuiBarComponent* _slider = nullptr;
    GuiLabelComponent* _label = nullptr;

  public:
    virtual void destroy();
  void init();
  virtual void setSlider(GuiBarComponent* slider);
    virtual void setLabel(GuiLabelComponent* label);
    virtual void onSliderChange();
};
