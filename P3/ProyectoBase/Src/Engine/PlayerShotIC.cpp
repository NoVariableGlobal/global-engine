#include "PlayerShotIC.h"
#include "Factory.h"
#include "FactoriesFactory.h"
#include "ComponentsManager.h"

#include "OgreRoot.h"

#include <json.h>

#include <iostream>

PlayerShotIC::PlayerShotIC() {}

PlayerShotIC::~PlayerShotIC() {}

void PlayerShotIC::handleInput(const SDL_Event& _event)
{
	if (_event.type == SDL_MOUSEBUTTONDOWN)
	{
		if(_event.button.button == SDL_BUTTON_LEFT)
			std::cout << '\n' << "PIUM PIUM !!" << '\n';
	}
}


// FACTORY INFRASTRUCTURE
class PlayerShotICFactory : public ComponentFactory {
public:
	PlayerShotICFactory() {};
	virtual Component* create(Entity* _father, Json::Value& _data, ComponentsManager* _componentManager)
	{
		PlayerShotIC* playerShot = new PlayerShotIC();

		playerShot->setFather(_father);

		_componentManager->addIC(playerShot);
		return playerShot;
	};
};

REGISTER_FACTORY("PlayerShotIC", PlayerShotIC);
