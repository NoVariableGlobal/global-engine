#pragma once
#include "GunC.h"
#include <string>
#include "Factory.h"

DECLARE_FACTORY(AutomaticRifleC);

class AutomaticRifleC : public GunC {
  public:
    AutomaticRifleC();
    ~AutomaticRifleC();

    virtual void destroy();
    virtual bool shoot();
};