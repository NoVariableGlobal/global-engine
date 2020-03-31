#pragma once
#include "PowerUpEC.h"

class PersistentPowerUpEC : public PowerUpEC {
  private:
    double timeEffect;
    bool startPicked;

  protected:
    virtual void setEffect(bool value) = 0;
    virtual void onDestroy();
    virtual std::string getName() = 0;

  public:
    void checkEvent();
};
