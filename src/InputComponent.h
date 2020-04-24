#pragma once

#include "Component.h"

#include <SDL_events.h>

// Abstract subcomponent from which every input component should inherit

class InputComponent : public Component {
  public:
    // interface for each input component handle method
    virtual void handleInput(const SDL_Event& event) = 0;

    // Destroys the InputComponent, setting itself as inactive and
    // removing itself from the scene.
    virtual void destroy();
};
