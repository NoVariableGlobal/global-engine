#include "WeaponControllerIC.h"
#include "ComponentsManager.h"
#include "Entity.h"
#include "FactoriesFactory.h"
#include "Factory.h"
#include "HandGunC.h"
#include "Scene.h"
#include <SDL.h>
#include <iostream>
#include <json.h>

WeaponControllerIC::WeaponControllerIC() {}

WeaponControllerIC::~WeaponControllerIC() {}

void WeaponControllerIC::destroy() {
    setActive(false);
    scene->getComponentsManager()->eraseIC(this);
}

void WeaponControllerIC::init() { currentGun = dynamic_cast<HandGunC*>(father->getComponent("HandGunC")); }

void WeaponControllerIC::handleInput(const SDL_Event& _event) {

    if (_event.type == SDL_KEYDOWN && _event.key.keysym.sym == SDLK_SPACE) {
        if (secondaryGun != nullptr) {
            GunC* aux = currentGun;
            currentGun = secondaryGun;
            secondaryGun = aux;
        }
    }
}

GunC* WeaponControllerIC::getCurrentGun() { return currentGun; }

void WeaponControllerIC::pickUpGun(std::string _gunName, GunC* _newGun) {
    // Remove old gun
    if (secondaryGun != nullptr) {
        scene->getComponentsManager()->eraseDC(secondaryGun);
    }

    // Add and equip new gun
    father->addComponent(_gunName, _newGun);
    secondaryGun = _newGun;
    currentGun = _newGun;
}

// FACTORY INFRASTRUCTURE
class WeaponControllerICFactory final : public ComponentFactory {
  public:
    WeaponControllerICFactory() = default;

    Component* create(Entity* _father, Json::Value& _data,
                      Scene* _scene) override {
        WeaponControllerIC* weaponControllerIC = new WeaponControllerIC();
        _scene->getComponentsManager()->addIC(weaponControllerIC);

        weaponControllerIC->setFather(_father);
        weaponControllerIC->setScene(_scene);
        weaponControllerIC->init();

        return weaponControllerIC;
    };
};

REGISTER_FACTORY("WeaponControllerIC", WeaponControllerIC);
