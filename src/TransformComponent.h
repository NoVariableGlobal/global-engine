#pragma once
#include "Component.h"
#include "Factory.h"

// FACTORY INFRASTRUCTURE DECLARATION
DECLARE_FACTORY(TransformComponent);

namespace Ogre {
    typedef float Real;
    template <int dims, typename T> class Vector;
    typedef Vector<3, Real> Vector3;
} // namespace Ogre

class TransformComponent : public Component {
  private:
    // Position of the entity in the 3D world
    Ogre::Vector3* _position = nullptr;
    // Rotation of the entity in the 3 axis
    Ogre::Vector3* _orientation = nullptr;
    // Scale of the entity in the 3 axis
    Ogre::Vector3* _scale = nullptr;

    // Original rotation of the entity in the 3 axis
    Ogre::Vector3* _originalOrientation = nullptr;

  public:
    TransformComponent();
    virtual ~TransformComponent();

    virtual void destroy();

    // Getters and setters
    Ogre::Vector3 getPosition() const;
    void setPosition(Ogre::Vector3 p);

    Ogre::Vector3 getOrientation();
    void setOrientation(Ogre::Vector3 r);

    Ogre::Vector3 getScale();
    void setScale(Ogre::Vector3 s);

    Ogre::Vector3 getOriginalOrientation();
    void setOriginalOrientation(Ogre::Vector3 r);
};
