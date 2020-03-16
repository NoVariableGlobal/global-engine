#include "RigidbodyPC.h"
#include "Factory.h"
#include "FactoriesFactory.h"
 
#include "ComponentsManager.h"
#include "PhysicsContext.h"
#include <btBulletDynamicsCommon.h>
#include <btBulletCollisionCommon.h>
#include "OgreVector3.h"
#include "Entity.h"
#include "TransformComponent.h"
#include "Scene.h"
#include <json.h>


RigidbodyPC::RigidbodyPC(Ogre::Vector3 _pos, Ogre::Vector3 _shape, float _mass, bool _trigger)
{
	body = PhysicsContext::instance()->createRB(_pos, _shape, _mass);
	setTrigger(_trigger);
}

RigidbodyPC::~RigidbodyPC()
{
	body = nullptr;
}

void RigidbodyPC::update()
{
	dynamic_cast<TransformComponent*>(father->getComponent("TransformComponent"))->
		setPosition(Ogre::Vector3(body->getWorldTransform().getOrigin().x(), body->getWorldTransform().getOrigin().y(), body->getWorldTransform().getOrigin().z()));
}

bool RigidbodyPC::collidesWith(std::string id)
{
	Entity* other = scene->getEntitybyId(id);

	if (body->checkCollideWith(dynamic_cast<RigidbodyPC*>(other->getComponent("Rigidbody"))->body))
		return true;
	else
		return false;
}

void RigidbodyPC::addForce(const Ogre::Vector3 _force, Ogre::Vector3 _relative_pos)
{
	if (_relative_pos == Ogre::Vector3(0.0f, 0.0f, 0.0f))
		body->applyCentralForce((btVector3(btScalar(_force.x), btScalar(_force.y), btScalar(_force.z))));
	else
		body->applyForce((btVector3(btScalar(_force.x), btScalar(_force.y), btScalar(_force.z))), (btVector3(btScalar(_relative_pos.x), btScalar(_relative_pos.y), btScalar(_relative_pos.z))));
}

void RigidbodyPC::setGravity(const Ogre::Vector3 _g)
{
	body->setGravity(btVector3(btScalar(_g.x), btScalar(_g.y), btScalar(_g.z)));
}

bool RigidbodyPC::isTrigger() const
{
	return trigger;
}

bool RigidbodyPC::isKinematic() const
{
	return kinematic;
}

bool RigidbodyPC::isStatic() const
{
	return stat;
}

void RigidbodyPC::setTrigger(bool _trigger)
{
	body->setCollisionFlags(body->getCollisionFlags() & (body->CF_NO_CONTACT_RESPONSE * trigger));
	trigger = _trigger;
}

void RigidbodyPC::setKinematic(bool _kinematic)
{
	body->setCollisionFlags(body->getCollisionFlags() & (body->CF_KINEMATIC_OBJECT * _kinematic));
	kinematic = _kinematic;
}

void RigidbodyPC::setStatic(bool _static)
{
	body->setCollisionFlags(body->getCollisionFlags() & (body->CF_STATIC_OBJECT * _static));
	stat = _static;
}

void RigidbodyPC::setFriction(float _friction)
{
	body->setFriction(_friction);
}

void RigidbodyPC::setRestitution(float _restitution)
{
	body->setRestitution(_restitution);
}

// FACTORY INFRASTRUCTURE
class RigidbodyPCFactory : public ComponentFactory {
public:
	RigidbodyPCFactory() {};

	virtual Component* create(Entity* _father, Json::Value& _data, Scene* scene)
	{
		RigidbodyPC* rb = new RigidbodyPC(Ogre::Vector3(_data["position"][0].asInt(), _data["position"][1].asInt(), _data["position"][2].asInt()),
											Ogre::Vector3(_data["shape"][0].asInt(), _data["shape"][1].asInt(), _data["shape"][2].asInt()), _data["mass"].asFloat(), _data["trigger"].asBool());
		rb->setFather(_father);
		rb->setScene(scene);

		TransformComponent* transform = dynamic_cast<TransformComponent*>(_father->getComponent("TransformComponent"));

		rb = new RigidbodyPC(transform->getPosition(), transform->getPosition(), 1, true);

		scene->getComponentsManager()->addPC(rb);
		return rb;
	};
};

REGISTER_FACTORY("RigidbodyPC", RigidbodyPC);