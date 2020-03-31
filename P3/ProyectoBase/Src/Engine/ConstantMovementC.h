#pragma once
#include "Component.h"
#include "Factory.h"

DECLARE_FACTORY(ConstantMovementC);

class ConstantMovementC : public Component {
  private:
    float speed;

  public:
    ConstantMovementC();
    virtual ~ConstantMovementC();

    virtual void destroy();

    // getter / Setters
    void setSpeed(float _speed);
    void setTimer(float _timer);

    float getSpeed();
};
