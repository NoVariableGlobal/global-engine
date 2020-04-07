#pragma once
#include "InputComponent.h"
#include "SoundComponent.h"

DECLARE_FACTORY(SoundTestIC);

class SoundTestIC : public InputComponent {
    SoundComponent* soundComponent_ = nullptr;

  public:
    void handleInput(const SDL_Event& _event) override;
};
