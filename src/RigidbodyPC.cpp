#include "RigidbodyPC.h"
#include "ComponentsManager.h"
#include "Entity.h"
#include "FactoriesFactory.h"
#include "PhysicsContext.h"
#include "Scene.h"
#include "TransformComponent.h"
#include <BulletCollision/NarrowPhaseCollision/btGjkEpaPenetrationDepthSolver.h>
#include <BulletCollision/NarrowPhaseCollision/btGjkPairDetector.h>
#include <BulletCollision/NarrowPhaseCollision/btPointCollector.h>
#include <Ogre.h>
#include <btBulletCollisionCommon.h>
#include <btBulletDynamicsCommon.h>
#include <json.h>

RigidbodyPC::RigidbodyPC(const Ogre::Vector3 pos, const Ogre::Vector3 shape,
                         const float mass) {
    body_ = PhysicsContext::getInstance()->createRB(pos, shape, mass);
}

RigidbodyPC::~RigidbodyPC() { body_ = nullptr; }

void RigidbodyPC::destroy() {
    PhysicsComponent::destroy();
    PhysicsContext::getInstance()->destroyRigidBody(body_);
}

void RigidbodyPC::setActive(const bool active) {
    Component::setActive(active);
    if (active) {
        PhysicsContext::getInstance()->getWorld()->addRigidBody(body_);
        // if (!trigger)
        //    body->setCollisionFlags(body->getCollisionFlags() &
        //                            ~btCollisionObject::CF_NO_CONTACT_RESPONSE);
        // body->forceActivationState(DISABLE_DEACTIVATION);
    }

    else {
        PhysicsContext::getInstance()->getWorld()->removeRigidBody(body_);
        // if (!trigger)
        //    body->setCollisionFlags(body->getCollisionFlags() |
        //                            btCollisionObject::CF_NO_CONTACT_RESPONSE);
        // body->forceActivationState(DISABLE_SIMULATION);
    }
}

void RigidbodyPC::update() {
    // Updates the transform of the father as the position of the rigidbody
    auto* transform = reinterpret_cast<TransformComponent*>(
        father_->getComponent("TransformComponent"));

    const auto worldTransform = body_->getWorldTransform();
    const auto origin = worldTransform.getOrigin();
    transform->setPosition(Ogre::Vector3(origin.x(), origin.y(), origin.z()));
}

bool RigidbodyPC::collidesWith(const std::string id) const {
    // Recieves an id of an entity and checks if our father is colliding with it
    if (!active_)
        return false;

    Entity* other = scene_->getEntityById(id);
    return collidesWithEntity(other);
}

bool RigidbodyPC::collidesWithEntity(Entity* other) const {
    auto* otherRigidBody =
        reinterpret_cast<RigidbodyPC*>(other->getComponent("RigidbodyPC"));
    if (!otherRigidBody->isActive())
        return false;

    btVoronoiSimplexSolver sGjkSimplexSolver;
    btGjkEpaPenetrationDepthSolver epaSolver;
    btPointCollector gjkOutput;

    btGjkPairDetector convexConvex(
        static_cast<btConvexShape*>(body_->getCollisionShape()),
        static_cast<btConvexShape*>(otherRigidBody->body_->getCollisionShape()),
        &sGjkSimplexSolver, &epaSolver);

    btGjkPairDetector::ClosestPointInput input;
    input.m_transformA = body_->getWorldTransform();
    input.m_transformB = otherRigidBody->body_->getWorldTransform();
    convexConvex.getClosestPoints(input, gjkOutput, nullptr);

    return gjkOutput.m_hasResult && gjkOutput.m_distance <= 0;
}

Entity* RigidbodyPC::collidesWithTag(const std::string tag) const {
    std::vector<Entity*> tagEntities = scene_->getEntitiesByTag(tag);

    for (auto it : tagEntities) {
        if (collidesWithEntity(it))
            return it;
    }

    return nullptr;
}

void RigidbodyPC::addForce(const Ogre::Vector3 force,
                           const Ogre::Vector3 relativePos) {
    if (!active_)
        return;

    if (relativePos == Ogre::Vector3(0.0f, 0.0f, 0.0f))
        body_->applyCentralForce((btVector3(
            btScalar(force.x), btScalar(force.y), btScalar(force.z))));
    else
        body_->applyForce(
            (btVector3(btScalar(force.x), btScalar(force.y),
                       btScalar(force.z))),
            (btVector3(btScalar(relativePos.x), btScalar(relativePos.y),
                       btScalar(relativePos.z))));
}

void RigidbodyPC::setGravity(const Ogre::Vector3 gravity) {
    if (!active_)
        return;
    body_->setGravity(btVector3(btScalar(gravity.x), btScalar(gravity.y),
                                btScalar(gravity.z)));
}

bool RigidbodyPC::isTrigger() const { return trigger_; }

bool RigidbodyPC::isKinematic() const { return kinematic_; }

bool RigidbodyPC::isStatic() const { return stat_; }

Ogre::Vector3 RigidbodyPC::getLinearVelocity() const {
    if (!active_)
        return Ogre::Vector3::NEGATIVE_UNIT_X;

    const btVector3 back = body_->getLinearVelocity();
    return Ogre::Vector3(back.x(), back.y(), back.z());
}

void RigidbodyPC::setTrigger(const bool trigger) {
    if (trigger)
        body_->setCollisionFlags(body_->getCollisionFlags() |
                                 btCollisionObject::CF_NO_CONTACT_RESPONSE);
    else
        body_->setCollisionFlags(body_->getCollisionFlags() &
                                 ~btCollisionObject::CF_NO_CONTACT_RESPONSE);

    trigger_ = trigger;
}

void RigidbodyPC::setKinematic(const bool kinematic) {

    if (kinematic)
        body_->setCollisionFlags(body_->getCollisionFlags() |
                                 btCollisionObject::CF_KINEMATIC_OBJECT);
    else
        body_->setCollisionFlags(body_->getCollisionFlags() &
                                 ~btCollisionObject::CF_KINEMATIC_OBJECT);
    kinematic_ = kinematic;
}

void RigidbodyPC::setStatic(const bool _static) {
    if (_static)
        body_->setCollisionFlags(body_->getCollisionFlags() |
                                 btCollisionObject::CF_STATIC_OBJECT);
    else
        body_->setCollisionFlags(body_->getCollisionFlags() &
                                 ~btCollisionObject::CF_STATIC_OBJECT);
    stat_ = _static;
}

void RigidbodyPC::setFriction(const float friction) {
    body_->setFriction(friction);
}

void RigidbodyPC::setRestitution(const float restitution) {
    if (!active_)
        return;

    body_->setRestitution(restitution);
}

void RigidbodyPC::setLinearVelocity(const Ogre::Vector3 vector) {
    if (!active_)
        return;

    body_->setLinearVelocity(btVector3(vector.x, vector.y, vector.z));
}

void RigidbodyPC::setPosition(const Ogre::Vector3 newPos) {
    if (!active_)
        return;
    btTransform initialTransform;
    initialTransform.setOrigin(btVector3(newPos.x, newPos.y, newPos.z));
    initialTransform.setRotation(body_->getOrientation());

    body_->setWorldTransform(initialTransform);
}
// FACTORY INFRASTRUCTURE DEFINITION

RigidbodyPCFactory::RigidbodyPCFactory() = default;

Component* RigidbodyPCFactory::create(Entity* _father, Json::Value& _data,
                                      Scene* _scene) {
    if (!_data["position"].isArray() || !_data["shape"].isArray() ||
        !_data["mass"].isInt())
        throw std::exception("RigidbodyPC: position/shape is not an array "
                             "or mass is not an int");
    int mass = _data["mass"].asInt();

    if (!_data["static"].isBool())
        throw std::exception("RigidbodyPC: static is not a boolean");
    if (_data["static"].asBool())
        mass = 0;

    RigidbodyPC* rb = new RigidbodyPC(
        Ogre::Vector3(_data["position"][0].asFloat(),
                      _data["position"][1].asFloat(),
                      _data["position"][2].asFloat()),
        Ogre::Vector3(_data["shape"][0].asFloat(), _data["shape"][1].asFloat(),
                      _data["shape"][2].asFloat()),
        static_cast<float>(mass));
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

    rb->setStatic(_data["static"].asBool());

    if (!_data["friction"].isInt())
        throw std::exception("RigidbodyPC: friction is not an int");
    rb->setFriction(_data["friction"].asFloat());

    if (!_data["restitution"].isInt())
        throw std::exception("RigidbodyPC: restitution is not an int");
    rb->setRestitution(_data["restitution"].asFloat());

    return rb;
};

DEFINE_FACTORY(RigidbodyPC);
