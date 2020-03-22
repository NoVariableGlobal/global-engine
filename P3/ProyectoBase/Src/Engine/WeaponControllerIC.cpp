#include "FactoriesFactory.h"
#include "Factory.h"
#include "WeaponControllerIC.h"
#include "Scene.h"
#include "ComponentsManager.h"
#include "Entity.h"
#include "HandGunC.h"
#include <SDL.h>
#include <iostream>
#include <json.h>

WeaponControllerIC::WeaponControllerIC() {}

WeaponControllerIC::~WeaponControllerIC() {}

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