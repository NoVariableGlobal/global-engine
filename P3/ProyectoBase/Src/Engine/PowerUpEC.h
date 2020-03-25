#pragma once

#include "EventComponent.h"

class PowerUpEC : public EventComponent {
  private:
    float durationTotal;
    float time;
    float timeStart;
    bool collisionWithPlayer;
    bool start;

  protected:
    bool picked;
  public:
    PowerUpEC();
    ~PowerUpEC();
    virtual void checkEvent();

    void setDuration(float _duration);
    bool getCollisionWithPlayer();
    bool timeDisappear();
};
