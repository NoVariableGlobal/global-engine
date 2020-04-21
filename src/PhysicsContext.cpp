#include "PhysicsContext.h"

#include "DebugDrawer.h"
#include "LinearMath/btIDebugDraw.h"
#include "OgreSDLContext.h"
#include <btBulletCollisionCommon.h>
#include <btBulletDynamicsCommon.h>

PhysicsContext* PhysicsContext::instance_ = nullptr;

PhysicsContext* PhysicsContext::getInstance() { return instance_; }

void PhysicsContext::init() { instance_ = new PhysicsContext(); }

PhysicsContext::PhysicsContext() = default;

PhysicsContext::~PhysicsContext() = default;

void PhysicsContext::init(const float gravity) {
    defaultCollisionConfiguration_ = new btDefaultCollisionConfiguration();
    collisionDispatcher_ =
        new btCollisionDispatcher(defaultCollisionConfiguration_);
    broadphaseInterface_ = new btDbvtBroadphase();
    sequentialImpulseConstraintSolver_ =
        new btSequentialImpulseConstraintSolver();

    discreteDynamicsWorld_ = new btDiscreteDynamicsWorld(
        collisionDispatcher_, broadphaseInterface_,
        sequentialImpulseConstraintSolver_, defaultCollisionConfiguration_);
    discreteDynamicsWorld_->setGravity(btVector3(0, gravity, 0));
    mDebugDrawer_ =
        new OgreDebugDrawer(OgreSDLContext::getInstance()->getSceneManager());
    mDebugDrawer_->setDebugMode(btIDebugDraw::DBG_DrawWireframe);
    discreteDynamicsWorld_->setDebugDrawer(mDebugDrawer_);
}
void PhysicsContext::destroyWorld() {
    destroyWorldContent();

    delete discreteDynamicsWorld_;
    discreteDynamicsWorld_ = nullptr;
    delete defaultCollisionConfiguration_;
    defaultCollisionConfiguration_ = nullptr;
    delete collisionDispatcher_;
    collisionDispatcher_ = nullptr;
    delete broadphaseInterface_;
    broadphaseInterface_ = nullptr;
    delete sequentialImpulseConstraintSolver_;
    sequentialImpulseConstraintSolver_ = nullptr;
    delete mDebugDrawer_;
    mDebugDrawer_ = nullptr;

    delete instance_;
    instance_ = nullptr;
}

void PhysicsContext::destroyWorldContent() {
    // We iterate from the size to 1, modifying `i` before we read it so the
    // range it reads is size - 1 to 0. This is also more efficient and safe as
    // it does not lose information by transforming a `size_t` into an `int`.
    auto i = ribs_.size();
    while (i != 0) {
        --i;
        discreteDynamicsWorld_->removeCollisionObject(ribs_[i]);

        delete ribs_[i];
        ribs_.pop_back();
    }

    i = shapes_.size();
    while (i != 0) {
        delete shapes_[--i];
        shapes_.pop_back();
    }

    i = states_.size();
    while (i != 0) {
        delete states_[--i];
        states_.pop_back();
    }
}

void PhysicsContext::destroyRigidBody(btRigidBody* body) {
    auto it = ribs_.begin();
    bool erased = false;
    while (it != ribs_.end() && !erased) {
        if (*it == body) {
            discreteDynamicsWorld_->removeCollisionObject(*it);
            delete *it;
            erased = true;
        } else
            ++it;
    }
    ribs_.erase(it);
}

void PhysicsContext::updateSimulation() {
    discreteDynamicsWorld_->stepSimulation(1.f / 60.f, 10);
#ifdef _DEBUG
    discreteDynamicsWorld_->debugDrawWorld();
#endif

    // TO DO: renders debug bodies
    // TO DO: check collisions
}

btDiscreteDynamicsWorld* PhysicsContext::getWorld() const {
    return discreteDynamicsWorld_;
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

    discreteDynamicsWorld_->addRigidBody(rb);
    ribs_.push_back(rb);
    shapes_.push_back(box);
    states_.push_back(motion);
    return rb;
}
