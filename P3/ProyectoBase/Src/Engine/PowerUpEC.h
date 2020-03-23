#pragma once

#include "EventComponent.h"

class PowerUpEC : public EventComponent {
  private:
    float durationTotal;
    float time;
    bool collisionWithPlayer;
    bool disappear = false;

  public:
    PowerUpEC();
    ~PowerUpEC();

    virtual void update();
    virtual void checkEvent() = 0;

    void setDuration(float _duration);
    bool getCollisionWithPlayer();
};
