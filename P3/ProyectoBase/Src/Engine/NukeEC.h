#pragma once
#include "ImmediatePowerUpEC.h"
#include "Factory.h"

DECLARE_FACTORY(NukeEC);

class NukeEC final : public ImmediatePowerUpEC {
  public:
    void onPick();
};
