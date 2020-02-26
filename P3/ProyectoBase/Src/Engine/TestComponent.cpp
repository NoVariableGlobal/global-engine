#include "TestComponent.h"

TestComponent::TestComponent() {}

TestComponent::~TestComponent() {}

void TestComponent::update() 
{
  // Whatever
}

Component* TestComponentFactory::create() {
  return new TestComponent();
}