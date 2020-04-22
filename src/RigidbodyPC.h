#pragma once
#include "Factory.h"
#include "PhysicsComponent.h"
#include <string>

// FACTORY INFRASTRUCTURE DECLARATION
DECLARE_FACTORY(RigidbodyPC);

namespace Ogre {
    typedef float Real;
    template <int Dims, typename T> class Vector;
    typedef Vector<3, Real> Vector3;
} // namespace Ogre

class btRigidBody;

class RigidbodyPC final : public PhysicsComponent {
    btRigidBody* body_ = nullptr;
    bool trigger_ = false;
    bool kinematic_ = false;
    bool stat_ = false;
    bool collision_ = false;

    bool collidesWithEntity(Entity* other) const;

  public:
    RigidbodyPC(Ogre::Vector3 pos, Ogre::Vector3 shape, float mass);
    ~RigidbodyPC();
    void destroy() override;
    void setActive(bool active) override;
    void update() override;

    // returns whether or not the entity this component is
    // attached to is colliding with another given entity
    bool collidesWith(std::string id) const;

    Entity* collidesWithTag(std::string tag) const;

    // Applies a force to the entity this component is attached to
    void addForce(Ogre::Vector3 force, Ogre::Vector3 relativePos);

    // Getters

    // Returns if an object is trigger
    bool isTrigger() const;

    // Returns if an object is kinematic
    bool isKinematic() const;

    // Returns if an object is static
    bool isStatic() const;

    // Get the linear velocity
    Ogre::Vector3 getLinearVelocity() const;

    // Setters

    // Gives gravity to the body
    void setGravity(Ogre::Vector3 gravity);

    // It gets if a body we want it to be trigger
    void setTrigger(bool trigger);

    // We say if we want a body to be kinematic
    void setKinematic(bool kinematic);

    // We say if we want a body to be static
    void setStatic(bool _static);

    // We put the friction value of a body
    void setFriction(float friction);

    // We put the restitution value of a body
    void setRestitution(float restitution);

    // Set linear velocity to the body
    void setLinearVelocity(Ogre::Vector3 vector);

    // Set up Position
    void setPosition(Ogre::Vector3 newPos);
};
