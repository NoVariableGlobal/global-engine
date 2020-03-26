#pragma once

#include "PowerUpC.h"

class ShotgunPowerUpC : public PowerUpC {

  public:
    virtual void destroy();

    void onPickUp();
};
