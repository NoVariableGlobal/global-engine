#pragma once

class btCollisionDispatcher;
class btBroadphaseInterface;
class btSequentialImpulseConstraintSolver;
class btDefaultCollisionConfiguration;
class btDiscreteDynamicsWorld;
class btRigidBody;

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

	btRigidBody* createRB();
};

