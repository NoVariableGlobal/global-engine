#pragma once

#include "PhysicsComponent.h"
#include "PhysicsContext.h"

class RigidbodyPC : public PhysicsComponent {
private:
	btRigidBody* body;
	bool trigger;
public:
	RigidbodyPC(Ogre::Vector3 _pos, Ogre::Vector3 _shape, float _mass, PhysicsContext* _physics);
	~RigidbodyPC();
};