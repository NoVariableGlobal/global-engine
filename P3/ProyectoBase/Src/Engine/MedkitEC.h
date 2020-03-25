#pragma once

#include "PowerUpEC.h"

class LifeC;

class MedkitEC : public PowerUpEC {
  public:
    MedkitEC();
    virtual ~MedkitEC();
    virtual void destroy();
    virtual void checkEvent();
};
