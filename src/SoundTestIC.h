#pragma once
#include "InputComponent.h"
#include "SoundComponent.h"

DECLARE_FACTORY(SoundTestIC);

class SoundTestIC final : public InputComponent {
    SoundComponent* soundComponent_ = nullptr;

  public:
    void handleInput(const SDL_Event& event) override;
};
