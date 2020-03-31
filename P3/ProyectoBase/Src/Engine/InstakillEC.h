#pragma once
#include "PersistentPowerUpEC.h"

class InstakillEC final : public PersistentPowerUpEC {
  public:
    void setEffect(bool value) override;
    std::string getName() override;
};
