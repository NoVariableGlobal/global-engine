#pragma once
#include "GunC.h"
#include <string>

class ShotgunC : public GunC {
  private:

  public:
    ShotgunC();
    ~ShotgunC();

	virtual void destroyMyself();
    virtual bool shoot();
};