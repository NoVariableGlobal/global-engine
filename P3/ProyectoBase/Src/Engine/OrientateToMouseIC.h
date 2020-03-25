#pragma once
#include "InputComponent.h"
class OrientateToMouseIC : public InputComponent {
  public:
    OrientateToMouseIC() = default;
    ~OrientateToMouseIC() = default;
    virtual void destroy();
    void handleInput(const SDL_Event& _event);
};
