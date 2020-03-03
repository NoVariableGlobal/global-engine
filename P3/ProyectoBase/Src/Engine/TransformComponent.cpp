#include "TransformComponent.h"

#include <json.h>
#include "Ogre.h"
#include "OgreVector3.h"
#include "Factory.h"
#include "FactoriesFactory.h"

TransformComponent::TransformComponent() 
{
	_position = new Ogre::Vector3();
	_scale = new Ogre::Vector3();
	_orientation = new Ogre::Vector3();
}

TransformComponent::~TransformComponent() 
{
	delete _position;
	delete _scale;
	delete _orientation;
}

Ogre::Vector3 TransformComponent::getPosition() { return *_position; }
void TransformComponent::setPosition(Ogre::Vector3 p) { *_position = p; }

Ogre::Vector3 TransformComponent::getOrientation() { return *_orientation; }
void TransformComponent::setOrientation(Ogre::Vector3 r) { *_orientation = r; }

Ogre::Vector3 TransformComponent::getScale() { return *_scale; }
void TransformComponent::setScale(Ogre::Vector3 s) { *_scale = s; }


// FACTORY INFRASTRUCTURE
class TransformComponentFactory : public ComponentFactory {
public:
	TransformComponentFactory() {};
	virtual Component* create(Entity* father, Json::Value& _data, ComponentsManager* componentManager)
	{
		TransformComponent* transformComponent = new TransformComponent();
		transformComponent->setFather(father);
		transformComponent->setPosition(Ogre::Vector3(_data["position"][0].asInt(), _data["position"][1].asInt(), _data["position"][2].asInt()));
		transformComponent->setOrientation(Ogre::Vector3(_data["orientation"][0].asInt(), _data["orientation"][1].asInt(), _data["orientation"][2].asInt()));
		transformComponent->setScale(Ogre::Vector3(_data["scale"][0].asInt(), _data["scale"][1].asInt(), _data["scale"][2].asInt()));

		return transformComponent;
	};
};

REGISTER_FACTORY("TransformComponent", TransformComponent);
