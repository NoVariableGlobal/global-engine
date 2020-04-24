#pragma once
#include "Component.h"
#include "Factory.h"

// FACTORY INFRASTRUCTURE DECLARATION
DECLARE_FACTORY(TransformComponent);

namespace Ogre {
    typedef float Real;
    template <int Dims, typename T> class Vector;
    typedef Vector<3, Real> Vector3;
} // namespace Ogre

class TransformComponent final : public Component {
    // Position of the entity in the 3D world
    Ogre::Vector3* position_ = nullptr;
    // Rotation of the entity in the 3 axis
    Ogre::Vector3* orientation_ = nullptr;
    // Scale of the entity in the 3 axis
    Ogre::Vector3* scale_ = nullptr;

    // Original rotation of the entity in the 3 axis
    Ogre::Vector3* originalOrientation_ = nullptr;

  public:
    TransformComponent();
    virtual ~TransformComponent();

    void destroy() override;

    // Getters and setters
    Ogre::Vector3 getPosition() const;
    void setPosition(Ogre::Vector3 p);

    Ogre::Vector3 getOrientation() const;
    void setOrientation(Ogre::Vector3 r);

    Ogre::Vector3 getScale() const;
    void setScale(Ogre::Vector3 s);

    Ogre::Vector3 getOriginalOrientation() const;
    void setOriginalOrientation(Ogre::Vector3 r);
};
