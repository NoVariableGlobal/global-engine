#include "TopDownPlayerMovementIC.h"
#include <SDL.h>
#include "OgreRoot.h"
#include "Factory.h"
#include "FactoriesFactory.h"
#include "Component.h"
#include "ComponentsManager.h"
#include <json.h>
// #include "RigidbodyPC"
#include <iostream>

TopDownPlayerMovementIC::TopDownPlayerMovementIC()
{
}

TopDownPlayerMovementIC::~TopDownPlayerMovementIC()
{
}

void TopDownPlayerMovementIC::handleInput(const SDL_Event& _event)
{
	if (_event.type == SDL_KEYDOWN) {
		// TO DO: send messages to rigidbody to move in a specific direction
		// RigidbodyPC* rb = dynamic_cast<RigidbodyPC*>(_father->getComponent("RigidbodyPC"));
		switch (_event.key.keysym.sym)
		{
		case SDLK_w:
			std::cout << '\n' << "MOVE UP" << '\n';
			// rb->addForce(Ogre::Vector3(0.0f, 0.0f, -_speed), Ogre::Vector3(0.0f, 0.0f, 0.0f));
			break;
		case SDLK_s:
			std::cout << '\n' << "MOVE DOWN" << '\n';
			// rb->addForce(Ogre::Vector3(0.0f, 0.0f, _speed), Ogre::Vector3(0.0f, 0.0f, 0.0f);
			break;
		case SDLK_a:
			std::cout << '\n' << "MOVE LEFT" << '\n';
			// rb->addForce(Ogre::Vector3(-_speed, 0.0f, 0.0f), Ogre::Vector3(0.0f, 0.0f, 0.0f);
			break;
		case SDLK_d:
			std::cout << '\n' << "MOVE RIGHT" << '\n';
			// rb->addForce(Ogre::Vector3(_speed, 0.0f, 0.0f), Ogre::Vector3(0.0f, 0.0f, 0.0f);
			break;
		}
	}
}

void TopDownPlayerMovementIC::setMovementSpeed(float speed)
{
	_speed = speed;
}

// TO DO: factory isnt called 
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

