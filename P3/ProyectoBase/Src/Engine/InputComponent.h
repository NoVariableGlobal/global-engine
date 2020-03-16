#pragma once

#include "Component.h"

#include <SDL_events.h>

class InputComponent : public Component 
{
	public:
		InputComponent();
		virtual ~InputComponent();
		virtual void handleInput(const SDL_Event& _event) = 0;

};
