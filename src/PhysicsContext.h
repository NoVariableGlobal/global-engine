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
} // namespace Ogre

class PhysicsContext {
  private:
    static PhysicsContext* _instance;

    btCollisionDispatcher* collisionDispatcher = nullptr;
    btBroadphaseInterface* broadphaseInterface = nullptr;
    btSequentialImpulseConstraintSolver* sequentialImpulseConstraintSolver =
        nullptr;
    btDefaultCollisionConfiguration* defaultCollisionConfiguration = nullptr;
    btDiscreteDynamicsWorld* discreteDynamicsWorld = nullptr;
    OgreDebugDrawer* mDebugDrawer = nullptr;

    std::vector<btRigidBody*> ribs;
    std::vector<btBoxShape*> shapes;
    std::vector<btMotionState*> states;
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
