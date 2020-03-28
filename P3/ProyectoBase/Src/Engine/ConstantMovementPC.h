#pragma once

#include "PhysicsComponent.h"

class ConstantMovementPC : public PhysicsComponent {
  private:
    float speed;
    int timer;    // every time the counter resets, speed is increased
    int counter;  // counter restarts every time it equals the timer

  public:
    ConstantMovementPC();
    virtual ~ConstantMovementPC();

    virtual void destroy();

    virtual void update();

    // getter / Setters
    void setSpeed(float _speed);
    void setTimer(float _timer);

    float getSpeed();
};
