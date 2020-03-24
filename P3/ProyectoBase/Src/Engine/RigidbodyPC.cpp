#include "RigidbodyPC.h"
#include "ComponentsManager.h"
#include "Entity.h"
#include "FactoriesFactory.h"
#include "Factory.h"
#include "OgreVector3.h"
#include "PhysicsContext.h"
#include "Scene.h"
#include "TransformComponent.h"
#include <BulletCollision/NarrowPhaseCollision/btGjkEpaPenetrationDepthSolver.h>
#include <BulletCollision/NarrowPhaseCollision/btGjkPairDetector.h>
#include <BulletCollision/NarrowPhaseCollision/btPointCollector.h>
#include <btBulletCollisionCommon.h>
#include <btBulletDynamicsCommon.h>
#include <json.h>

RigidbodyPC::RigidbodyPC(Ogre::Vector3 _pos, Ogre::Vector3 _shape,
                         float _mass) {
    body = PhysicsContext::getInstance()->createRB(_pos, _shape, _mass);
}

RigidbodyPC::~RigidbodyPC() { body = nullptr; }

void RigidbodyPC::destroyMyself() {
    setActive(false);
    scene->getComponentsManager()->erasePC(this);
}

void RigidbodyPC::setActive(bool active) { 
    Component::setActive(active); 
    if (active)
        body->forceActivationState(DISABLE_DEACTIVATION);
    else
        body->forceActivationState(DISABLE_SIMULATION);
}

void RigidbodyPC::update() {
    // Updates the transform of the father as the position of the rigidbody
    dynamic_cast<TransformComponent*>(
        father->getComponent("TransformComponent"))
        ->setPosition(Ogre::Vector3(body->getWorldTransform().getOrigin().x(),
                                    body->getWorldTransform().getOrigin().y(),
                                    body->getWorldTransform().getOrigin().z()));
}

bool RigidbodyPC::collidesWith(std::string id) {
    // Recieves an id of an entity and checks if our father is colliding with it
    Entity* other = scene->getEntitybyId(id);

    btVoronoiSimplexSolver sGjkSimplexSolver;
    btGjkEpaPenetrationDepthSolver epaSolver;
    btPointCollector gjkOutput;

    btGjkPairDetector convexConvex((btConvexShape*)body->getCollisionShape(),
                                   (btConvexShape*)dynamic_cast<RigidbodyPC*>(
                                       other->getComponent("RigidbodyPC"))
                                       ->body->getCollisionShape(),
                                   &sGjkSimplexSolver, &epaSolver);

    btGjkPairDetector::ClosestPointInput input;
    input.m_transformA = body->getWorldTransform();
    input.m_transformB =
        dynamic_cast<RigidbodyPC*>(other->getComponent("RigidbodyPC"))
            ->body->getWorldTransform();
    convexConvex.getClosestPoints(input, gjkOutput, 0);

    if (gjkOutput.m_hasResult && gjkOutput.m_distance <= 0)
        return true;
    else
        return false;
}

void RigidbodyPC::addForce(const Ogre::Vector3 _force,
                           Ogre::Vector3 _relative_pos) {
    if (_relative_pos == Ogre::Vector3(0.0f, 0.0f, 0.0f))
        body->applyCentralForce((btVector3(
            btScalar(_force.x), btScalar(_force.y), btScalar(_force.z))));
    else
        body->applyForce(
            (btVector3(btScalar(_force.x), btScalar(_force.y),
                       btScalar(_force.z))),
            (btVector3(btScalar(_relative_pos.x), btScalar(_relative_pos.y),
                       btScalar(_relative_pos.z))));
}

void RigidbodyPC::setGravity(const Ogre::Vector3 _g) {
    body->setGravity(btVector3(btScalar(_g.x), btScalar(_g.y), btScalar(_g.z)));
}

bool RigidbodyPC::isTrigger() const { return trigger; }

bool RigidbodyPC::isKinematic() const { return kinematic; }

bool RigidbodyPC::isStatic() const { return stat; }

void RigidbodyPC::setTrigger(bool _trigger) {
    body->setCollisionFlags(body->getCollisionFlags() &
                            (body->CF_NO_CONTACT_RESPONSE * trigger));
    trigger = _trigger;
}

void RigidbodyPC::setKinematic(bool _kinematic) {
    body->setCollisionFlags(body->getCollisionFlags() &
                            (body->CF_KINEMATIC_OBJECT * _kinematic));
    kinematic = _kinematic;
}

void RigidbodyPC::setStatic(bool _static) {
    body->setCollisionFlags(body->getCollisionFlags() &
                            (body->CF_STATIC_OBJECT * _static));
    stat = _static;
}

void RigidbodyPC::setFriction(float _friction) { body->setFriction(_friction); }

void RigidbodyPC::setRestitution(float _restitution) {
    body->setRestitution(_restitution);
}

void RigidbodyPC::setLinearVelocity(Ogre::Vector3 _v) {
    body->setLinearVelocity(btVector3(_v.x, _v.y, _v.z));
}


void RigidbodyPC::setPosition(Ogre::Vector3 newPos) {
    btTransform initialTransform;
    initialTransform.setOrigin(btVector3(newPos.x, newPos.y, newPos.z));
    initialTransform.setRotation(body->getOrientation());

    body->setWorldTransform(initialTransform);
}
// FACTORY INFRASTRUCTURE
class RigidbodyPCFactory final : public ComponentFactory {
  public:
    RigidbodyPCFactory() = default;

    Component* create(Entity* _father, Json::Value& _data,
                      Scene* _scene) override {
        if (!_data["position"].isArray() || !_data["shape"].isArray() ||
            !_data["mass"].isInt())
            throw std::exception("RigidbodyPC: position/shape is not an array "
                                 "or mass is not an int");

        RigidbodyPC* rb =
            new RigidbodyPC(Ogre::Vector3(_data["position"][0].asFloat(),
                                          _data["position"][1].asFloat(),
                                          _data["position"][2].asFloat()),
                            Ogre::Vector3(_data["shape"][0].asFloat(),
                                          _data["shape"][1].asFloat(),
                                          _data["shape"][2].asFloat()),
                            _data["mass"].asFloat());
        _scene->getComponentsManager()->addPC(rb);

        rb->setFather(_father);
        rb->setScene(_scene);

        if (!_data["gravity"].isArray())
            throw std::exception("RigidbodyPC: gravity is not an array");
        rb->setGravity(Ogre::Vector3(_data["gravity"][0].asFloat(),
                                     _data["gravity"][1].asFloat(),
                                     _data["gravity"][2].asFloat()));

        if (!_data["trigger"].isBool())
            throw std::exception("RigidbodyPC: trigger is not a boolean");
        rb->setTrigger(_data["trigger"].asBool());

        if (!_data["kinematic"].isBool())
            throw std::exception("RigidbodyPC: kinematic is not a boolean");
        rb->setKinematic(_data["kinematic"].asBool());

        if (!_data["static"].isBool())
            throw std::exception("RigidbodyPC: static is not a boolean");
        rb->setStatic(_data["static"].asBool());

        if (!_data["friction"].isInt())
            throw std::exception("RigidbodyPC: friction is not an int");
        rb->setFriction(_data["friction"].asFloat());

        if (!_data["restitution"].isInt())
            throw std::exception("RigidbodyPC: restitution is not an int");
        rb->setRestitution(_data["restitution"].asFloat());

        return rb;
    };
};

REGISTER_FACTORY("RigidbodyPC", RigidbodyPC);