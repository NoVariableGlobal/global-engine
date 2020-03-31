#pragma once
#include "PersistentPowerUpEC.h"
#include "Factory.h"

DECLARE_FACTORY(InfiniteAmmoEC);
class InfiniteAmmoEC final : public PersistentPowerUpEC {
  public:
    void setEffect(bool value) override;
    std::string getName() override;
};
