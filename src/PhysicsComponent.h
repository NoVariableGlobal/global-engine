#pragma once

#include "Component.h"

// Abstract subcomponent from which every physics component should inherit

class PhysicsComponent : public Component {
  public:
    PhysicsComponent();
    virtual ~PhysicsComponent();
    virtual void update() = 0;

    // Destroys the PhysicsComponent, setting itself as inactive and
    // removing itself from the scene.
    virtual void destroy();
};