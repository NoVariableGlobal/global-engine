#pragma once
#include "PowerUpEC.h"

class GunC;

class InfiniteAmmoEC : public PowerUpEC {
  private:
    GunC* gun_;
    double time;
    double timeEffect;
    bool startPicked;

  public:
    InfiniteAmmoEC();
    ~InfiniteAmmoEC();
    virtual void destroy();
    virtual void checkEvent();
    void setTimeEffect(float _time);
    bool timeDisappearEffect();
    void setPickedTime(float _time);
};
