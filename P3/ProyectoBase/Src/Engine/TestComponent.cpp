#include <json.h>

#include "TestComponent.h"
#include "Factory.h"
#include "FactoriesFactory.h"
#include "Ogre.h"
#include "OgreVector3.h"
#include "Entity.h"
#include "ComponentsManager.h"

TestComponent::TestComponent() { _color = new Ogre::Vector3(); }

TestComponent::~TestComponent() 
{
	delete _color;
}

void TestComponent::update() 
{
  // Whatever
}

void TestComponent::setMaterial(std::string material)
{
	_material = material;
}

void TestComponent::setColor(Ogre::Vector3 color)
{
	*_color = color;
}

std::string TestComponent::getMaterial()
{
	return _material;
}

Ogre::Vector3* TestComponent::getColor()
{
	return _color;
}

// FACTORY INFRASTRUCTURE
class TestComponentFactory : public ComponentFactory {
public:
	TestComponentFactory() {};

	virtual Component* create(Entity* father, Json::Value& _data, ComponentsManager* componentManager)
	{
		TestComponent* testComponent = new TestComponent();
		testComponent->setFather(father);
		testComponent->setMaterial(_data["material"].asString());
		testComponent->setColor(Ogre::Vector3(_data["color"][0].asInt(), _data["color"][1].asInt(), _data["color"][2].asInt()));

		componentManager->addPC(testComponent);
		return testComponent;
	};
};

REGISTER_FACTORY("TestComponent", TestComponent);
