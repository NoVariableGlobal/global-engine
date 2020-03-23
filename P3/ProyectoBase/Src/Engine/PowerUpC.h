#pragma once

#include "Component.h"
#include <string>
#include <vector>

class PowerUpC : public Component {
  private:
    float probability;
    float duration;

    bool instantaneous;

  public:
    virtual void onPickUp();

    void setProbability(float _probability);
    void setDuration(float _duration);
    void isInstantaneous(bool _instantaneous);
};
