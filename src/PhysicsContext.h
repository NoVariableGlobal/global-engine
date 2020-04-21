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
    template <int Dims, typename T> class Vector;
    typedef Vector<3, Real> Vector3;
} // namespace Ogre

class PhysicsContext {
    static PhysicsContext* instance_;

    btCollisionDispatcher* collisionDispatcher_ = nullptr;
    btBroadphaseInterface* broadphaseInterface_ = nullptr;
    btSequentialImpulseConstraintSolver* sequentialImpulseConstraintSolver_ =
        nullptr;
    btDefaultCollisionConfiguration* defaultCollisionConfiguration_ = nullptr;
    btDiscreteDynamicsWorld* discreteDynamicsWorld_ = nullptr;
    OgreDebugDrawer* mDebugDrawer_ = nullptr;

    std::vector<btRigidBody*> ribs_;
    std::vector<btBoxShape*> shapes_;
    std::vector<btMotionState*> states_;
    PhysicsContext();
    ~PhysicsContext();

  public:
    static PhysicsContext* getInstance();
    static void init();

    void init(float gravity); // Start a world with gravity and physics
    void destroyWorld();      // Destroys all variables related to physics
    void destroyWorldContent();
    void destroyRigidBody(btRigidBody* body);
    void updateSimulation(); // Update the world's physics

    btDiscreteDynamicsWorld* getWorld() const;
    btRigidBody* createRB(Ogre::Vector3 pos, Ogre::Vector3 shape, float mass);
};
