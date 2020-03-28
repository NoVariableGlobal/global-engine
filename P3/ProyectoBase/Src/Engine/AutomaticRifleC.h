#pragma once
#include "GunC.h"
#include <string>

class AutomaticRifleC : public GunC {
  public:
    AutomaticRifleC();
    ~AutomaticRifleC();

    virtual void destroy();
    virtual bool shoot();
};