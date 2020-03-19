#pragma once

#include "Component.h"

//Abstract class for every component that has update but is not physic or input
class EventComponent : public Component {
public:
	EventComponent();
	virtual ~EventComponent();
	virtual void checkEvent() = 0;

};