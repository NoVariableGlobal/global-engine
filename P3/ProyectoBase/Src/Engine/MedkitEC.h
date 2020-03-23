#pragma once

#include "PowerUpEC.h"

class LifeC;

class MedkitEC : public PowerUpEC {
  public:
    virtual void update();
    virtual void onPickUp();
};
