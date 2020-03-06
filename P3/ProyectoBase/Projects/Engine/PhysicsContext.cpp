#include "PhysicsContext.h"

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
	// TO DO: discreteDynamicsWorld->debugDrawWorld() renders debug bodies
	// TO DO: check collisions
}

void PhysicsContext::checkCollisions()
{
}
