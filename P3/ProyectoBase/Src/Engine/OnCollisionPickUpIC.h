#pragma once

#include "InputComponent.h"
#include <string>

class RigidbodyPC;

class OnCollisionPickUpIC : public InputComponent {
  private:
    RigidbodyPC* rb;
    std::string objectName;

  public:
    OnCollisionPickUpIC();
    ~OnCollisionPickUpIC() = default;

    void handleInput(const SDL_Event& _event);

    void setObjectName(std::string _name);
};
