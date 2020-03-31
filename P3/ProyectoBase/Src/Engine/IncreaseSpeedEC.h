#pragma once
#include "PersistentPowerUpEC.h"

class IncreaseSpeedEC final : public PersistentPowerUpEC {
  private:
    double speedIncrement_ = 0.0;
    double originalSpeed_ = 0.0;

  public:
    void setSpeedIncrement(double value);
    void setEffect(bool value) override;
    std::string getName() override;
};