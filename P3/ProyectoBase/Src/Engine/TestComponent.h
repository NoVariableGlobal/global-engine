#pragma

#include "PhysicsComponent.h"

// COMPONENT CODE
class TestComponent : public PhysicsComponent {
public:
	TestComponent();
	virtual ~TestComponent();

	virtual void update();
};

// FACTORY INFRASTRUCTURE
class TestComponentFactory : public ComponentFactory {
public:
	TestComponentFactory() {};
	TestComponent* create();
};

class TestComponentFactoryRegister
{
	TestComponentFactoryRegister() { factory.insert({ "TestComponent", new TestComponentFactory() }); }
};

TestComponentFactoryRegister testComponentFactoryRegister;