#include <json.h>

#include "TestComponent.h"
#include "Factory.h"
#include "FactoriesFactory.h"
#include "Ogre.h"
#include "OgreVector3.h"

//#define TestComponentRegister() (FactoriesFactory::instance()->insert("TestComponent", new TestComponentFactory()));
//#define execute TestComponentRegister();

TestComponent::TestComponent() { _color = new Ogre::Vector3(); }

TestComponent::~TestComponent() {}

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
	virtual Component* create(Json::Value& _data) 
	{
		TestComponent* testComponent = new TestComponent();
		testComponent->setMaterial(_data["material"].asString());
		testComponent->setColor(Ogre::Vector3(_data["color"][0].asInt(), _data["color"][1].asInt(), _data["color"][2].asInt()));
		return testComponent;
	};
};

class TestComponentFactoryRegister
{
public:
	TestComponentFactoryRegister() { FactoriesFactory::instance()->insert("TestComponent", new TestComponentFactory()); }
};


TestComponentFactoryRegister testComponentFactoryRegister;