#pragma once

#include "PhysicsComponent.h"

class PowerUpPC : public PhysicsComponent {
  private:
    float durationTotal;
    float time;
    float timeStart;
    bool collisionWithPlayer;
    bool disappear;
    bool start;

  public:
    PowerUpPC();
    ~PowerUpPC();
    virtual void update();

    void setDuration(float _duration);
    bool getCollisionWithPlayer();
    bool timeDisappear();
};
