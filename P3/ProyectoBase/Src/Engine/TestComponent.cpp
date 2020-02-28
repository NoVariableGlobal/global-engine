#include "TestComponent.h"
#include "Factory.h"
#include "FactoriesFactory.h"

TestComponent::TestComponent() {}

TestComponent::~TestComponent() {}

void TestComponent::update() 
{
  // Whatever
}



// FACTORY INFRASTRUCTURE
class TestComponentFactory : public ComponentFactory {
public:
	TestComponentFactory() {};
	virtual Component* create() { return new TestComponent(); };
};

class TestComponentFactoryRegister
{
public:
	TestComponentFactoryRegister() { FactoriesFactory::instance()->insert("TestComponent", new TestComponentFactory()); }
};


TestComponentFactoryRegister testComponentFactoryRegister;