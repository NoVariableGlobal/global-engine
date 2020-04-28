#pragma once

#include "Component.h"
#include "Factory.h"

#include <string>

// FACTORY INFRASTRUCTURE DECLARATION
DECLARE_FACTORY(AmbientLightC);

namespace Ogre {
    typedef float Real;
    template <int dims, typename T> class Vector;
    typedef Vector<3, Real> Vector3;
} // namespace Ogre

class AmbientLightC : public Component {
  private:
    Ogre::Vector3* currentColour_ = nullptr;

  public:
    AmbientLightC();
    virtual ~AmbientLightC();

    virtual void destroy();

    virtual void setActive(bool active);

    // Sets a given material to the object
    void setColour(Ogre::Vector3 colour);

    Ogre::Vector3 getCurrentColor();
};
