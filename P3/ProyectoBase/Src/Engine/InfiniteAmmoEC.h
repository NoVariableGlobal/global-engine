#pragma once
#include "PersistentPowerUpEC.h"

class InfiniteAmmoEC final : public PersistentPowerUpEC {
  public:
    void setEffect(bool value) override;
    std::string getName() override;
};
