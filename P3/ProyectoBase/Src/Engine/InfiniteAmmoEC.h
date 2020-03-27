#pragma once
#include "PowerUpEC.h"

class GunC;

class InfiniteAmmoEC : public PowerUpEC {
  private:
    GunC* gun_;

  public:
    InfiniteAmmoEC();
    ~InfiniteAmmoEC();
    virtual void destroy();
    virtual void checkEvent();
};
