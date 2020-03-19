#pragma once

#include "Component.h"

// Abstract subcomponent from which every physics component should inherit

class PhysicsComponent : public Component {
  public:
    PhysicsComponent();
    virtual ~PhysicsComponent();
    virtual void update() = 0;
};