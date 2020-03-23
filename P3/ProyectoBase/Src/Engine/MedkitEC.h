#pragma once

#include "PowerUpEC.h"

class LifeC;

class MedkitEC : public PowerUpEC {
  private:
    double probability;
    double time;
    double timeEffect;
    double currentDuration;

	bool picked;

  public:
    MedkitEC();
    ~MedkitEC();

    virtual void update();
    virtual void checkEvent();

    void setProbability(float _probability);
    void setTime(float _time);
    void setTimeEffect(float _timeEffect);

    void onCollisionActivate();
    bool checkCollision();
};
