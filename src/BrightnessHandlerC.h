#include "Factory.h"
#include "SpecialFloatHandlerC.h"
#pragma once

// FACTORY INFRASTRUCTURE DECLARATION
DECLARE_FACTORY(BrightnessHandlerComponent);

class BrightnessHandlerComponent final : public SpecialFloatHandlerComponent {
  public:
    void updateFloat(float value) override;
    float getFloat() override;
};
