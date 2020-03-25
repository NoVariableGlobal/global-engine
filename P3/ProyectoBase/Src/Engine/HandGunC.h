#pragma once
#include "GunC.h"
#include <string>

class HandGunC : public GunC {
  private:

  public:
    HandGunC();
    ~HandGunC();

    virtual void destroy();

    virtual bool shoot();
};
