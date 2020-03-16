#include "PlayerMovementIC.h"
#include <SDL.h>
#include "OgreRoot.h"
#include "Factory.h"
#include "FactoriesFactory.h"
#include "Component.h"
#include "ComponentsManager.h"
#include "Scene.h"
#include <json.h>
#include "TransformComponent.h"
#include <Entity.h>
#include <iostream>

PlayerMovementIC::PlayerMovementIC()
{
}

PlayerMovementIC::~PlayerMovementIC()
{
}

void PlayerMovementIC::handleInput(const SDL_Event& _event)
{
	if (_event.type == SDL_KEYDOWN) {
		TransformComponent* transform = dynamic_cast<TransformComponent*>(father->getComponent("TransformComponent"));
		std::cout << transform->getPosition().x << " " << transform->getPosition().y << " " << transform->getPosition().z << "\n";
		switch (_event.key.keysym.sym)
		{
		case SDLK_w:
			transform->setPosition(transform->getPosition() + Ogre::Vector3(0.0f, 0.0f, -_speed));
			break;
		case SDLK_s:
			transform->setPosition(transform->getPosition() + Ogre::Vector3(0.0f, 0.0f, _speed));
			break;
		case SDLK_a:
			transform->setPosition(transform->getPosition() + Ogre::Vector3(-_speed, 0.0f, 0.0f));
			break;
		case SDLK_d:
			transform->setPosition(transform->getPosition() + Ogre::Vector3(_speed, 0.0f, 0.0f));
			break;
		}
	}
}

void PlayerMovementIC::setMovementSpeed(float speed)
{
	_speed = speed;
}

class PlayerMovementICFactory : public ComponentFactory {
public:
	PlayerMovementICFactory() {};
	virtual Component* create(Entity* _father, Json::Value& _data, Scene* scene)
	{
		PlayerMovementIC* playerMovement = new PlayerMovementIC();

		playerMovement->setFather(_father);

		playerMovement->setMovementSpeed(_data["speed"].asFloat());

		scene->getComponentsManager()->addIC(playerMovement);
		return playerMovement;
	};
};

REGISTER_FACTORY("PlayerMovementIC", PlayerMovementIC);

