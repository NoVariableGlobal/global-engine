#pragma once
#include "ImmediatePowerUpEC.h"
#include "Factory.h"

// FACTORY INFRASTRUCTURE DECLARATION
DECLARE_FACTORY(MedkitEC);

class MedkitEC final : public ImmediatePowerUpEC {
  public:
    void onPick();
};
