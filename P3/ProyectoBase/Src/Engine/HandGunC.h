#pragma once
#include "GunC.h"
#include <string>
#include "Factory.h"

// FACTORY INFRASTRUCTURE DECLARATION
DECLARE_FACTORY(HandGunC);

class HandGunC : public GunC {
  private:

  public:
    HandGunC();
    ~HandGunC();

    virtual void destroy();

    virtual bool shoot();
};
