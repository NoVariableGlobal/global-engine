#include "LifeComponent.h"

#include "OgreRoot.h"
#include "OgreVector3.h"
#include "Factory.h"
#include "FactoriesFactory.h"
#include "ComponentsManager.h"

#include <json.h>

LifeComponent::LifeComponent() {}

LifeComponent::~LifeComponent() {}

float LifeComponent::getLife() { return currentLife; }

void LifeComponent::setLife(int _life)
{
	currentLife = _life;
}

int LifeComponent::getTotalLife() { return totalLife; }

void LifeComponent::setTotalLife(int _life)
{
	totalLife = _life;
}

void LifeComponent::doDamage(float _damage)
{  
	currentLife -= _damage;

	if (currentLife < 0)
		currentLife = 0;
}

void LifeComponent::heal(float _heal)
{
	currentLife += _heal;

	if (currentLife > totalLife)
		currentLife = totalLife;
}


// FACTORY INFRASTRUCTURE
class LifeComponentFactory : public ComponentFactory {
public:
	LifeComponentFactory() {};
	virtual Component* create(Entity* _father, Json::Value& _data, ComponentsManager* _componentManager)
	{
		LifeComponent* lifeComponent = new LifeComponent();

		lifeComponent->setFather(_father);

		if (!_data["life"].isInt()) { /*EXCEPCION*/ }
		lifeComponent->setTotalLife(_data["life"].asInt());
		lifeComponent->setLife(_data["life"].asInt());

		_componentManager->addTC(lifeComponent);
		return lifeComponent;
	};
};

REGISTER_FACTORY("LifeComponent", LifeComponent);
