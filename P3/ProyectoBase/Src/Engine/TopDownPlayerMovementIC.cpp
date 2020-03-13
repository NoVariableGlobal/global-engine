#include "TopDownPlayerMovementIC.h"
#include <SDL.h>
#include "Factory.h"
#include "FactoriesFactory.h"
#include "Component.h"
#include "ComponentsManager.h"
#include <json.h>
// #include "RigidbodyPC"

TopDownPlayerMovementIC::TopDownPlayerMovementIC()
{
}

TopDownPlayerMovementIC::~TopDownPlayerMovementIC()
{
}

void TopDownPlayerMovementIC::handleInput(const SDL_Event& _event)
{
	if (_event.type == SDL_KEYDOWN) {
		// RigidbodyPC* rb = dynamic_cast<RigidbodyPC*>(_father->getComponent("RigidbodyPC"));
		switch (_event.key.keysym.sym)
		{
		case SDLK_w:
			// rb->addForce(Ogre::Vector3(0.0f, 0.0f, -1.0f), Ogre::Vector3(0.0f, 0.0f, 0.0f));
			break;
		case SDLK_s:
			// rb->addForce(Ogre::Vector3(0.0f, 0.0f, 1.0f), Ogre::Vector3(0.0f, 0.0f, 0.0f);
			break;
		case SDLK_a:
			// rb->addForce(Ogre::Vector3(-1.0f, 0.0f, 0.0f), Ogre::Vector3(0.0f, 0.0f, 0.0f);
			break;
		case SDLK_d:
			// rb->addForce(Ogre::Vector3(1.0f, 0.0f, 0.0f), Ogre::Vector3(0.0f, 0.0f, 0.0f);
			break;
		}
	}
}

void TopDownPlayerMovementIC::setMovementSpeed(float speed)
{
	_speed = speed;
}

// FACTORY INFRASTRUCTURE
class TopDownPlayerMovementICFactory : public ComponentFactory {
public:
	TopDownPlayerMovementICFactory() {};
	virtual Component* create(Entity* _father, Json::Value& _data, ComponentsManager* _componentManager)
	{
		TopDownPlayerMovementIC* playerMovement = new TopDownPlayerMovementIC();

		playerMovement->setFather(_father);

		playerMovement->setMovementSpeed(_data["speed"].asFloat());

		_componentManager->addIC(playerMovement);
		return playerMovement;
	};
};

REGISTER_FACTORY("TopDownPlayerMovementIC", TopDownPlayerMovementIC);

