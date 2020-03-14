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
	OgreDebugDrawer* mDebugDrawer;
	btDiscreteDynamicsWorld* discreteDynamicsWorld;

	std::vector<btRigidBody*> ribs;
	std::vector<btBoxShape*> shapes;
	std::vector<btMotionState*> states;
public:

	static PhysicsContext* instance();
	PhysicsContext();
	~PhysicsContext();

	void init(float _gravity);
	void destroyWorld();
	void destroyWorldContent();
	void updateSimulation();

	btDiscreteDynamicsWorld* getWorld();
	btRigidBody* createRB(Ogre::Vector3 pos, Ogre::Vector3 shape, float mass);
};

