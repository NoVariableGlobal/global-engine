#pragma once

#include "InputComponent.h"

#include <string>

namespace Ogre {
    typedef float Real;
    template <int dims, typename T> class Vector;
    typedef Vector<3, Real> Vector3;
} // namespace Ogre

class ChangeGravityIC : public InputComponent {
  private:
    float speed;
    std::string mLeft;
    std::string mRight;

    bool movingIzq = true;

  public:
    ChangeGravityIC();
    virtual ~ChangeGravityIC();

    // On space bar down, change the rigibody gravity
    virtual void handleInput(const SDL_Event& _event);

    // Set the speed
    void setSpeed(float _speed);
    // Set the left material
    void setMaterialLeft(std::string _mLeft);
    // Set the right material
    void setMaterialRight(std::string _mRight);
};