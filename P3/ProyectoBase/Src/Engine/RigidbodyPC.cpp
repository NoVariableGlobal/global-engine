#include "RigidbodyPC.h"
#include "PhysicsComponent.h"
#include "PhysicsContext.h"


RigidbodyPC::RigidbodyPC(Ogre::Vector3 _pos, Ogre::Vector3 _shape, float _mass, PhysicsContext* _physics, bool _trigger)
{
	body = _physics->createRB(_pos, _shape, _mass);
	trigger = _trigger;
}

RigidbodyPC::~RigidbodyPC()
{
}

void RigidbodyPC::update()
{
}

void RigidbodyPC::addForce(const Ogre::Vector3& _force, Ogre::Vector3 _relative_pos)
{
	if (_relative_pos == Ogre::Vector3(0.0f, 0.0f, 0.0f))
		body->applyCentralForce((btVector3(btScalar(_force.x), btScalar(_force.y), btScalar(_force.z))));
	else
		body->applyForce((btVector3(btScalar(_force.x), btScalar(_force.y), btScalar(_force.z))), (btVector3(btScalar(_relative_pos.x), btScalar(_relative_pos.y), btScalar(_relative_pos.z))));
}

void RigidbodyPC::setGravity(const Ogre::Vector3& _g)
{
	body->setGravity(btVector3(btScalar(_g.x), btScalar(_g.y), btScalar(_g.z)));
}

bool RigidbodyPC::isTrigger() const
{
	return trigger;
}
