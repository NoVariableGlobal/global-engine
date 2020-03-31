#pragma once
#include "PowerUpEC.h"
#include <string>

class PersistentPowerUpEC : public PowerUpEC {
  private:
    bool activeEffect_ = false;

  protected:
    virtual void setEffect(bool value) = 0;
    virtual void onDestroy();
    virtual std::string getName() = 0;

  public:
    void checkEvent();
};
