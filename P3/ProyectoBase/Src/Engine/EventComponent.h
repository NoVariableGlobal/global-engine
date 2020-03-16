#pragma once

#include "Component.h"

class EventComponent : public Component {
public:
	EventComponent();
	virtual ~EventComponent();
	virtual void checkEvent() = 0;

};