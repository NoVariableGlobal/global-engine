#pragma once
#include "InputComponent.h"

#include "Factory.h"

// FACTORY INFRASTRUCTURE DECLARATION
DECLARE_FACTORY(OrientateToMouseIC);
class OrientateToMouseIC : public InputComponent {
  public:
    OrientateToMouseIC() = default;
    ~OrientateToMouseIC() = default;
    virtual void destroy();
    void handleInput(const SDL_Event& _event);
};
