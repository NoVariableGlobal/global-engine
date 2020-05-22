#pragma once
#include "Factory.h"
#include "SpecialFloatHandlerC.h"

// FACTORY INFRASTRUCTURE DECLARATION
DECLARE_FACTORY(VolumeHandlerComponent);

class VolumeHandlerComponent final : public SpecialFloatHandlerComponent {
  public:
    virtual void updateFloat(float value);
    virtual float getFloat();
};
