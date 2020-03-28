#pragma once

#include "PowerUpEC.h"

class LifeC;

class NukeEC : public PowerUpEC {
  public:
    NukeEC();
    virtual ~NukeEC();
    virtual void destroy();
    virtual void checkEvent();
};
