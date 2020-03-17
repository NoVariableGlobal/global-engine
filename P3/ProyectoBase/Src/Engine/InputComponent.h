#pragma once

#include "Component.h"

#include <SDL_events.h>

// Abstract subcomponent from which every input component should inherit

class InputComponent : public Component 
{
	public:
		InputComponent();
		virtual ~InputComponent();
		virtual void handleInput(const SDL_Event& _event) = 0;

};
