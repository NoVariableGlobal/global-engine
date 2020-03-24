#pragma once

#include "PowerUpEC.h"

class IncreaseSpeedEC : public PowerUpEC {
  public:
	  // probabilidad : 20%
    IncreaseSpeedEC();
    virtual ~IncreaseSpeedEC();
    virtual void checkEvent();
};
