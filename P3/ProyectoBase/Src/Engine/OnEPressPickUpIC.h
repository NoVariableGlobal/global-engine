#pragma once
#include "InputComponent.h"

#include <string>
#include "Factory.h"

DECLARE_FACTORY(OnEPressPickUpIC);
class RigidbodyPC;

class OnEPressPickUpIC : public InputComponent {
  private:
    RigidbodyPC* rb = nullptr;
    std::string objectName;

  public:
    OnEPressPickUpIC() = default;
    ~OnEPressPickUpIC() = default;

    void handleInput(const SDL_Event& _event);

    void setObjectName(std::string _name);
};
