#pragma once
#include "PersistentPowerUpEC.h"
#include "Factory.h"

DECLARE_FACTORY(InstakillEC);

class InstakillEC final : public PersistentPowerUpEC {
  public:
    void setEffect(bool value) override;
    std::string getName() override;
};
