#pragma once

#include "PhysicsComponent.h"
#include "PhysicsContext.h"

#include <btBulletDynamicsCommon.h>
#include <btBulletCollisionCommon.h>
#include "LinearMath/btIDebugDraw.h"
#include "DebugDrawer.h"
#include "OgreSDLContext.h"

class RigidbodyPC : public PhysicsComponent {
private:
	btRigidBody* body = nullptr;
	bool trigger;
	bool kinematic;
	bool stat;
public:
	RigidbodyPC(Ogre::Vector3 _pos, Ogre::Vector3 _shape, float _mass, PhysicsContext* _physics, bool _trigger);
	~RigidbodyPC();
	virtual void update();

	void addForce(const Ogre::Vector3& _force, Ogre::Vector3 _relative_pos = { 0.0f, 0.0f, 0.0f });
	bool isTrigger() const;
	bool isKinematic() const;
	bool isTriggerStatic() const;
	void setGravity(const Ogre::Vector3& _g);
	void setTrigger(bool _trigger);
	void setKinematic(bool _kinematic);
	void setStatic(bool _static);

};