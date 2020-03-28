#pragma once

#include "PowerUpC.h"

class AutomaticRiflePowerUpC : public PowerUpC {

  public:
    virtual void destroy();

    void onPickUp();
};