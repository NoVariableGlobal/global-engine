#include "TransformComponent.h"

#include <json.h>
#include "OgreRoot.h"
#include "OgreVector3.h"
#include "Factory.h"
#include "FactoriesFactory.h"
#include "ComponentsManager.h"
#include "Scene.h"

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
	virtual Component* create(Entity* _father, Json::Value& _data, Scene* scene)
	{
		TransformComponent* transformComponent = new TransformComponent();

		transformComponent->setFather(_father);
		transformComponent->setScene(scene);

		if (!_data["position"].isArray()) throw std::exception("TransformComponent: position is not an array");
		transformComponent->setPosition(Ogre::Vector3(_data["position"][0].asFloat(), _data["position"][1].asFloat(), _data["position"][2].asFloat()));

		if (!_data["orientation"].isArray())  throw std::exception("TransformComponent: orientation is not an array");
		transformComponent->setOrientation(Ogre::Vector3(_data["orientation"][0].asFloat(), _data["orientation"][1].asFloat(), _data["orientation"][2].asFloat()));

		if (!_data["scale"].isArray()) throw std::exception("TransformComponent: scale is not an array");
		transformComponent->setScale(Ogre::Vector3(_data["scale"][0].asFloat(), _data["scale"][1].asFloat(), _data["scale"][2].asFloat()));

		scene->getComponentsManager()->addDC(transformComponent);

		return transformComponent;
	}
};

REGISTER_FACTORY("TransformComponent", TransformComponent);
