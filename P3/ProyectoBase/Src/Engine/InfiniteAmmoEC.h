#pragma once
#include "PowerUpEC.h"

class GunC;

class InfiniteAmmoEC : public PowerUpEC {
  private:
    GunC* gun_;

    double timeEffect;
  public:
    InfiniteAmmoEC();
    ~InfiniteAmmoEC();
    virtual void destroy();
    virtual void checkEvent();
};
