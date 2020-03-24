#pragma once

#include "EventComponent.h"

class PowerUpPC : public EventComponent {
  private:
    float durationTotal;
    float time;
    float timeStart;
    bool collisionWithPlayer;
    bool start;

  protected:
    bool picked;
  public:
    PowerUpPC();
    ~PowerUpPC();
    virtual void checkEvent();

    void setDuration(float _duration);
    bool getCollisionWithPlayer();
    bool timeDisappear();
};
