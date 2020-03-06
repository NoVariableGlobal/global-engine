#pragma once

#include <btBulletDynamicsCommon.h>
#include <btBulletCollisionCommon.h>

class PhysicsContext
{
private:
	static PhysicsContext* _instance;

	btCollisionDispatcher* collisionDispatcher;
	btBroadphaseInterface* broadphaseInterface;
	btSequentialImpulseConstraintSolver* sequentialImpulseConstraintSolver;
	btDefaultCollisionConfiguration* defaultCollisionConfiguration;

	btDiscreteDynamicsWorld* discreteDynamicsWorld;
public:
	static PhysicsContext* instance();
	PhysicsContext();
	~PhysicsContext();

	void init(float _gravity);
	void updateSimulation();
	void checkCollisions();
};

