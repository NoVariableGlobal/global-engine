#pragma once
#include "PowerUpEC.h"
class InstakillEC : public PowerUpEC {
  private:
    double time;
    double timeEffect;
    bool startPicked;

  public:
    InstakillEC();
    ~InstakillEC();
    virtual void destroy();
    virtual void checkEvent();

    void setTimeEffect(float _time);
    bool timeDisappearEffect();
};
