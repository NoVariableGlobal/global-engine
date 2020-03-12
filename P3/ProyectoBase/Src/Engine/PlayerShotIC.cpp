#include "PlayerShotIC.h"

#include <json.h>
#include "OgreRoot.h"
#include "OgreVector3.h"
#include "Factory.h"
#include "FactoriesFactory.h"
#include "ComponentsManager.h"

PlayerShotIC::PlayerShotIC() {}

PlayerShotIC::~PlayerShotIC() {}


// FACTORY INFRASTRUCTURE
class PlayerShotICFactory : public ComponentFactory {
public:
	PlayerShotICFactory() {};
	virtual Component* create(Entity* _father, Json::Value& _data, ComponentsManager* _componentManager)
	{
		PlayerShotIC* playerShot = new PlayerShotIC();

		playerShot->setFather(_father);

		_componentManager->addTC(playerShot);
		return playerShot;
	};
};

REGISTER_FACTORY("PlayerShotIC", PlayerShotIC);
