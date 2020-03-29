#pragma once
#include "InputComponent.h"
#include <string>

class GunC;
class WeaponControllerIC : public InputComponent {

  private:
    GunC* currentGun = nullptr;
    GunC* secondaryGun = nullptr;

  public:
    WeaponControllerIC();
    virtual ~WeaponControllerIC();
    virtual void destroy();

    void init();
    // Updates the entity's transform's
    // position upon pressing WASD keys
    virtual void handleInput(const SDL_Event& _event);

    GunC* getCurrentGun();
    GunC* getSecondaryGun();
    void pickUpGun(std::string _gunName);
};
