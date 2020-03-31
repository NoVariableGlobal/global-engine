#pragma once
#include "PowerUpEC.h"

class ImmediatePowerUpEC : public PowerUpEC {
  protected:
    virtual void onPick() = 0;

  public:
    virtual void checkEvent();
};
