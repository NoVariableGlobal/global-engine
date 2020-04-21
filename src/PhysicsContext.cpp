#include "PhysicsContext.h"

#include "DebugDrawer.h"
#include "LinearMath/btIDebugDraw.h"
#include "OgreSDLContext.h"
#include <btBulletCollisionCommon.h>
#include <btBulletDynamicsCommon.h>

PhysicsContext* PhysicsContext::_instance = nullptr;

PhysicsContext* PhysicsContext::getInstance() { return _instance; }

void PhysicsContext::init() { _instance = new PhysicsContext(); }

PhysicsContext::PhysicsContext() = default;

PhysicsContext::~PhysicsContext() = default;

void PhysicsContext::init(const float gravity) {
    defaultCollisionConfiguration = new btDefaultCollisionConfiguration();
    collisionDispatcher =
        new btCollisionDispatcher(defaultCollisionConfiguration);
    broadphaseInterface = new btDbvtBroadphase();
    sequentialImpulseConstraintSolver =
        new btSequentialImpulseConstraintSolver();

    discreteDynamicsWorld = new btDiscreteDynamicsWorld(
        collisionDispatcher, broadphaseInterface,
        sequentialImpulseConstraintSolver, defaultCollisionConfiguration);
    discreteDynamicsWorld->setGravity(btVector3(0, gravity, 0));
    mDebugDrawer =
        new OgreDebugDrawer(OgreSDLContext::getInstance()->getSceneManager());
    mDebugDrawer->setDebugMode(btIDebugDraw::DBG_DrawWireframe);
    discreteDynamicsWorld->setDebugDrawer(mDebugDrawer);
}
void PhysicsContext::destroyWorld() {
    destroyWorldContent();

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

    delete _instance;
    _instance = nullptr;
}

void PhysicsContext::destroyWorldContent() {
    // We iterate from the size to 1, modifying `i` before we read it so the
    // range it reads is size - 1 to 0. This is also more efficient and safe as
    // it does not lose information by transforming a `size_t` into an `int`.
    auto i = ribs.size();
    while (i != 0) {
        --i;
        discreteDynamicsWorld->removeCollisionObject(ribs[i]);

        delete ribs[i];
        ribs.pop_back();
    }

    i = shapes.size();
    while (i != 0) {
        delete shapes[--i];
        shapes.pop_back();
    }

    i = states.size();
    while (i != 0) {
        delete states[--i];
        states.pop_back();
    }
}

void PhysicsContext::destroyRigidBody(btRigidBody* body) {
    auto it = ribs.begin();
    bool erased = false;
    while (it != ribs.end() && !erased) {
        if (*it == body) {
            discreteDynamicsWorld->removeCollisionObject(*it);
            delete *it;
            erased = true;
        } else
            ++it;
    }
    ribs.erase(it);
}

void PhysicsContext::updateSimulation() {
    discreteDynamicsWorld->stepSimulation(1.f / 60.f, 10);
#ifdef _DEBUG
    discreteDynamicsWorld->debugDrawWorld();
#endif

    // TO DO: renders debug bodies
    // TO DO: check collisions
}

btDiscreteDynamicsWorld* PhysicsContext::getWorld() const {
    return discreteDynamicsWorld;
}

btRigidBody* PhysicsContext::createRB(const Ogre::Vector3 pos,
                                      const Ogre::Vector3 shape,
                                      const float mass) {
    btTransform t;
    t.setIdentity();
    t.setOrigin(btVector3(pos.x, pos.y, pos.z));
    btBoxShape* box = new btBoxShape(btVector3(shape.x, shape.y, shape.z));
    btMotionState* motion = new btDefaultMotionState(t);
    btRigidBody::btRigidBodyConstructionInfo info(mass, motion, box);
    btRigidBody* rb = new btRigidBody(info);
    rb->forceActivationState(DISABLE_DEACTIVATION);

    discreteDynamicsWorld->addRigidBody(rb);
    ribs.push_back(rb);
    shapes.push_back(box);
    states.push_back(motion);
    return rb;
}
