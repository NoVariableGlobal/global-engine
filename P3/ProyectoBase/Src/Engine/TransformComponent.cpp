#include "TransformComponent.h"

#include <json.h>
#include "OgreRoot.h"
#include "OgreVector3.h"
#include "Factory.h"
#include "FactoriesFactory.h"
#include "ComponentsManager.h"

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
	virtual Component* create(Entity* _father, Json::Value& _data, ComponentsManager* _componentManager)
	{
		try {
			TransformComponent* transformComponent = new TransformComponent();

			transformComponent->setFather(_father);

			if (!_data["position"].isArray())
			{
				throw std::invalid_argument("Invalid argument is not array");
			}
			transformComponent->setPosition(Ogre::Vector3(_data["position"][0].asInt(), _data["position"][1].asInt(), _data["position"][2].asInt()));

			if (!_data["orientation"].isArray())
			{
				throw std::invalid_argument("Invalid argument is not array");
			}
			transformComponent->setOrientation(Ogre::Vector3(_data["orientation"][0].asInt(), _data["orientation"][1].asInt(), _data["orientation"][2].asInt()));

			if (!_data["scale"].isArray())
			{
				throw std::invalid_argument("Invalid argument is not array");
			}
			transformComponent->setScale(Ogre::Vector3(_data["scale"][0].asInt(), _data["scale"][1].asInt(), _data["scale"][2].asInt()));

			_componentManager->addTC(transformComponent);
			return transformComponent;
		}
		catch (std::invalid_argument const& invArg) {
			printf("%s \n", invArg.what());
			return NULL;
		}
	};
};

REGISTER_FACTORY("TransformComponent", TransformComponent);
