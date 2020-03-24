#pragma once

#include "PowerUpC.h"

class ShotgunPowerUpC : public PowerUpC {

  public:
    virtual void destroyMyself();

    void onPickUp();
};
