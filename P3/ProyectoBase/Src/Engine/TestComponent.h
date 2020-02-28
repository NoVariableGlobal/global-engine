#pragma once

#include "PhysicsComponent.h"

// COMPONENT CODE
class TestComponent : public PhysicsComponent {
public:
	TestComponent();
	virtual ~TestComponent();

	virtual void update();
};