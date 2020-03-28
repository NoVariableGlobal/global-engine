#pragma once

#include "PhysicsComponent.h"

namespace Ogre {
    typedef float Real;
    template <int dims, typename T> class Vector;
    typedef Vector<3, Real> Vector3;
} // namespace Ogre

class RigidBody;

class ConstantMovementPC : public PhysicsComponent {
  private:
    //btRigidBody* rb = nullptr;
    /*bool trigger = false;
    bool kinematic = false;
    bool stat = false;
    bool collision = false;*/
    float speed = 0;

  public:
    ConstantMovementPC();
    virtual ~ConstantMovementPC();

    virtual void destroy();

	virtual void update();

    // getter / Setters
    void setSpeed(float _speed);

    float getSpeed();
};
