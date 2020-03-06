#pragma once

#include "../Component.h"


class PhysicsComponent : public Component {
public:
	PhysicsComponent();
	virtual ~PhysicsComponent();
	virtual void update() = 0;

};