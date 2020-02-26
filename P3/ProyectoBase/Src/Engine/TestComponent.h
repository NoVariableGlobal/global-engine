#pragma once

#include "PhysicsComponent.h"
#include "Factory.h"

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
	virtual Component* create();
};

class TestComponentFactoryRegister
{
	public:
		TestComponentFactoryRegister() { factory.insert({ "TestComponent", new TestComponentFactory() }); }
};

TestComponentFactoryRegister testComponentFactoryRegister;