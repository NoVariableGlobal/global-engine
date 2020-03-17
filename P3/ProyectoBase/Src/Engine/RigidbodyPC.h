#pragma once
#include "PhysicsComponent.h"
#include <string>

namespace Ogre {
	typedef float Real;
	template <int dims, typename T> class Vector;
	typedef Vector<3, Real> Vector3;
}

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
	bool isTrigger() const;
	bool isKinematic() const;
	bool isStatic() const;

	// Setters
	void setGravity(const Ogre::Vector3 _g);
	void setTrigger(bool _trigger);
	void setKinematic(bool _kinematic);
	void setStatic(bool _static);
	void setFriction(float _friction);
	void setRestitution(float _restitution);
};