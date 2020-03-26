#pragma once

#include "Component.h"

class PowerUpC : public Component {
  private:
    float duration;
    bool instantaneous;

  public:
    virtual void onPickUp() = 0;

    void setDuration(float _duration);
    void isInstantaneous(bool _instantaneous);
};
