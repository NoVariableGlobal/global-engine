#pragma once

#include "PowerUpEC.h"
#include "Factory.h"


// FACTORY INFRASTRUCTURE DECLARATION
DECLARE_FACTORY(MedkitEC);
class LifeC;

class MedkitEC : public PowerUpEC {
  public:
    MedkitEC();
    virtual ~MedkitEC();
    virtual void destroy();
    virtual void checkEvent();
};
