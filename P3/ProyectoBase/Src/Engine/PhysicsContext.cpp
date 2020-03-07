#include "PhysicsContext.h"

#include <btBulletDynamicsCommon.h>
#include <btBulletCollisionCommon.h>
PhysicsContext* PhysicsContext::_instance = nullptr;

PhysicsContext* PhysicsContext::instance()
{
	if (_instance == nullptr) _instance = new PhysicsContext();
	return _instance;
}

PhysicsContext::PhysicsContext()
{
	
}

PhysicsContext::~PhysicsContext()
{
	delete defaultCollisionConfiguration;
	delete collisionDispatcher;
	delete broadphaseInterface;
	delete sequentialImpulseConstraintSolver;

	delete discreteDynamicsWorld;
}

void PhysicsContext::init(float _gravity)
{
	defaultCollisionConfiguration = new btDefaultCollisionConfiguration();
	collisionDispatcher = new btCollisionDispatcher(defaultCollisionConfiguration);
	broadphaseInterface = new btDbvtBroadphase();
	sequentialImpulseConstraintSolver = new btSequentialImpulseConstraintSolver;

	discreteDynamicsWorld = new btDiscreteDynamicsWorld(collisionDispatcher, broadphaseInterface, sequentialImpulseConstraintSolver, defaultCollisionConfiguration);
	discreteDynamicsWorld->setGravity(btVector3(0, _gravity, 0));
}

void PhysicsContext::updateSimulation()
{
	discreteDynamicsWorld->stepSimulation(1.f / 60.f, 10);
	discreteDynamicsWorld->debugDrawWorld();
	// TO DO: renders debug bodies
	// TO DO: check collisions
}

void PhysicsContext::checkCollisions()
{
	
}

btRigidBody* PhysicsContext::createRB()
{
	btTransform t;
	t.setIdentity();
	btBoxShape* box = new btBoxShape(t.getOrigin());
	btMotionState* motion = new btDefaultMotionState(t);
	btRigidBody::btRigidBodyConstructionInfo info(1.0, motion, box);
	btRigidBody* rb = new btRigidBody(info);

	discreteDynamicsWorld->addRigidBody(rb);

	return rb;
}
