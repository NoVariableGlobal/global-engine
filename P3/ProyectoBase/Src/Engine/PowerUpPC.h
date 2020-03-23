#pragma once

#include "PhysicsComponent.h"

class PowerUpPC : public PhysicsComponent {
  private:
    float durationTotal;
    float time;
    bool collisionWithPlayer;
    bool disappear;

  public:
    PowerUpPC();
    ~PowerUpPC();
    virtual void update();

    void setDuration(float _duration);
    bool getCollisionWithPlayer();
};
