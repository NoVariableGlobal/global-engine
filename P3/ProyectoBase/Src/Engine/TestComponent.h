#pragma once
#include "PhysicsComponent.h"

#include <string>

namespace Ogre {
    typedef float Real;
    template <int dims, typename T> class Vector;
    typedef Vector<3, Real> Vector3;
} // namespace Ogre

// COMPONENT CODE
class TestComponent : public PhysicsComponent {
  private:
    std::string _material;
    Ogre::Vector3* _color;

  public:
    TestComponent();
    virtual ~TestComponent();
    virtual void update();

    void setMaterial(std::string material);
    void setColor(Ogre::Vector3 color);

    std::string getMaterial();
    Ogre::Vector3* getColor();
};