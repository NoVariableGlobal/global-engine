#include "RigidbodyPC.h"
#include "PhysicsContext.h"

RigidbodyPC::RigidbodyPC(Ogre::Vector3 _pos, Ogre::Vector3 _shape, float _mass, PhysicsContext* _physics)
{
	body = _physics->createRB(_pos, _shape, _mass);
}

RigidbodyPC::~RigidbodyPC()
{
}
