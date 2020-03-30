#pragma once
#include "PowerUpEC.h"

class InstakillEC : public PowerUpEC {
  private:
    double time;
    double timeEffect;
    bool startPicked;

    void setEffect(bool effect);

  public:
    InstakillEC();
    ~InstakillEC();
    virtual void checkEvent();

    void setTimeEffect(float _time);
    bool timeDisappearEffect();
};
