#pragma once

#include "PowerUpC.h"
#include <string>

class GunPowerUpC : public PowerUpC {
    std::string _gunId;
  public:
    virtual void destroy();

    void onPickUp();

    void setGunId(const std::string& gunId);
};
