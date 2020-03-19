#pragma once
#include "PhysicsComponent.h"
#include <string>

namespace Ogre {
    typedef float Real;
    template <int dims, typename T> class Vector;
    typedef Vector<3, Real> Vector3;
} // namespace Ogre

class btRigidBody;

class RigidbodyPC : public PhysicsComponent {
  private:
    btRigidBody* body = nullptr;
    bool trigger = false;
    bool kinematic = false;
    bool stat = false;
    bool Collision = false;

  public:
    RigidbodyPC(Ogre::Vector3 _pos, Ogre::Vector3 _shape, float _mass);
    ~RigidbodyPC();
    virtual void update();

    // returns whether or not the entity this component is
    // attached to is colliding with another given entity
    bool collidesWith(std::string id);

    // Applies a force to the entity this component is attached to
    void addForce(const Ogre::Vector3 _force, Ogre::Vector3 _relativePos);

    // Getters
    bool isTrigger() const;   // Returns if an object is trigger
    bool isKinematic() const; // Returns if an object is kinematic
    bool isStatic() const;    // Returns if an object is static

    // Setters
    void setGravity(const Ogre::Vector3 _g); // Gives gravity to the body
    void
    setTrigger(bool _trigger); // It gets if a body we want it to be trigger
    void
    setKinematic(bool _kinematic); // We say if we want a body to be kinematic
    void setStatic(bool _static);  // We say if we want a body to be static
    void setFriction(float _friction); // We put the friction value of a body
    void setRestitution(
        float _restitution); // We put the restitution value of a body
};