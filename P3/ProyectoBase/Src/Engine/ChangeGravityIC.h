#pragma once

#include "InputComponent.h"

namespace Ogre {
    typedef float Real;
    template <int dims, typename T> class Vector;
    typedef Vector<3, Real> Vector3;
} // namespace Ogre

class ChangeGravityIC : public InputComponent {
  private:
    float speed;

    bool movingIzq = true;

  public:
    ChangeGravityIC();
    virtual ~ChangeGravityIC();

    // On mouse button down, tells a gun component to fire a shot
    virtual void handleInput(const SDL_Event& _event);

    // Set the speed
    void setSpeed(float _speed);
};