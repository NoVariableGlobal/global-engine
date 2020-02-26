#include "TestComponent.h"
#include <iostream>

TestComponent::TestComponent() {}

TestComponent::~TestComponent() {}

void TestComponent::update() override {
  // Whatever
}

TestComponent* TestComponentFactory::create() override {
  std::cout << "Created new TestComponent";
  return new TestComponent();
}