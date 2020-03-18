#include "PhysicsContext.h"

#include <btBulletDynamicsCommon.h>
#include <btBulletCollisionCommon.h>
#include "LinearMath/btIDebugDraw.h"
#include "DebugDrawer.h"
#include "OgreSDLContext.h"

PhysicsContext* PhysicsContext::_instance = nullptr;

PhysicsContext* PhysicsContext::getInstance()
{
	return _instance;
}

void PhysicsContext::init()
{
	_instance = new PhysicsContext();
}

PhysicsContext::PhysicsContext() {}

PhysicsContext::~PhysicsContext() {}

void PhysicsContext::init(float _gravity)
{
	defaultCollisionConfiguration = new btDefaultCollisionConfiguration();
	collisionDispatcher = new btCollisionDispatcher(defaultCollisionConfiguration);
	broadphaseInterface = new btDbvtBroadphase();
	sequentialImpulseConstraintSolver = new btSequentialImpulseConstraintSolver();

	discreteDynamicsWorld = new btDiscreteDynamicsWorld(collisionDispatcher, broadphaseInterface, sequentialImpulseConstraintSolver, defaultCollisionConfiguration);
	discreteDynamicsWorld->setGravity(btVector3(0, _gravity, 0));
	mDebugDrawer = new OgreDebugDrawer(OgreSDLContext::getInstance()->getSceneManager());
	mDebugDrawer->setDebugMode(btIDebugDraw::DBG_DrawWireframe);
	discreteDynamicsWorld->setDebugDrawer(mDebugDrawer);
}

void PhysicsContext::destroyWorld()
{
	delete discreteDynamicsWorld;
	discreteDynamicsWorld = nullptr;
	delete defaultCollisionConfiguration;
	defaultCollisionConfiguration = nullptr;
	delete collisionDispatcher;
	collisionDispatcher = nullptr;
	delete broadphaseInterface;
	broadphaseInterface = nullptr;
	delete sequentialImpulseConstraintSolver;
	sequentialImpulseConstraintSolver = nullptr;
	delete mDebugDrawer;
	mDebugDrawer = nullptr;

	destroyWorldContent();

	delete _instance;
	_instance = nullptr;
}

void PhysicsContext::destroyWorldContent()
{
	
	int size = ribs.size();
	for (int i = size - 1; i >= 0; i--)
	{
		delete ribs[i];
		ribs.pop_back();
	}

	size = shapes.size();
	for (int i = size - 1; i >= 0; i--)
	{
		delete shapes[i];
		shapes.pop_back();
	}

	size = states.size();
	for (int i = size - 1; i >= 0; i--)
	{
		delete states[i];
		states.pop_back();
	}
}

void PhysicsContext::updateSimulation()
{
	discreteDynamicsWorld->stepSimulation(1.f / 60.f, 10);
	discreteDynamicsWorld->debugDrawWorld();
	
	// TO DO: renders debug bodies
	// TO DO: check collisions
}

btDiscreteDynamicsWorld* PhysicsContext::getWorld()
{
	return discreteDynamicsWorld;
}

btRigidBody* PhysicsContext::createRB(Ogre::Vector3 pos, Ogre::Vector3 shape, float mass)
{
	btTransform t;
	t.setIdentity();
	t.setOrigin(btVector3(pos.x, pos.y, pos.z) );
	btBoxShape* box = new btBoxShape(btVector3(shape.x, shape.y, shape.z));
	btMotionState* motion = new btDefaultMotionState(t);
	btRigidBody::btRigidBodyConstructionInfo info(mass, motion, box);
	btRigidBody* rb = new btRigidBody(info);


	discreteDynamicsWorld->addRigidBody(rb);
	ribs.push_back(rb);
	shapes.push_back(box);
	states.push_back(motion);
	return rb;
}
