#pragma once
#include <vector>

class btCollisionDispatcher;
class btBroadphaseInterface;
class btSequentialImpulseConstraintSolver;
class btDefaultCollisionConfiguration;
class btDiscreteDynamicsWorld;
class btRigidBody;
class OgreDebugDrawer;
class btBoxShape;
class btMotionState;

namespace Ogre {
	typedef float Real;
	template <int dims, typename T> class Vector;
	typedef Vector<3, Real> Vector3;
}

class PhysicsContext
{
private:
	static PhysicsContext* _instance;

	btCollisionDispatcher* collisionDispatcher;
	btBroadphaseInterface* broadphaseInterface;
	btSequentialImpulseConstraintSolver* sequentialImpulseConstraintSolver;
	btDefaultCollisionConfiguration* defaultCollisionConfiguration;
  btDiscreteDynamicsWorld* discreteDynamicsWorld;
	OgreDebugDrawer* mDebugDrawer;

	std::vector<btRigidBody*> ribs;
	std::vector<btBoxShape*> shapes;
	std::vector<btMotionState*> states;
	PhysicsContext();
	~PhysicsContext();
public:
	static PhysicsContext* getInstance();
	static void init();

	void init(float _gravity);
	void destroyWorld();
	void destroyWorldContent();
	void updateSimulation();

	btRigidBody* createRB(Ogre::Vector3 pos, Ogre::Vector3 shape, float mass);
};

