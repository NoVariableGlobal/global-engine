#include "PlayerShotIC.h"
#include "AutomaticEC.h"
#include "ComponentsManager.h"
#include "Entity.h"
#include "FactoriesFactory.h"
#include "Factory.h"
#include "GunC.h"
#include "OgreRoot.h"
#include "Scene.h"
#include "WeaponControllerIC.h"
#include <iostream>
#include <json.h>

PlayerShotIC::PlayerShotIC() {}

PlayerShotIC::~PlayerShotIC() {}

void PlayerShotIC::handleInput(const SDL_Event& _event) {
    bool automatic = (dynamic_cast<WeaponControllerIC*>(
                          father->getComponent("WeaponControllerIC")))
                         ->getCurrentGun()
                         ->getautomatic();
    if (_event.type == SDL_MOUSEBUTTONDOWN) {
        if (_event.button.button == SDL_BUTTON_LEFT) {
            // TODO: Tell gun component to fire a shot
            if (!automatic)
                (dynamic_cast<WeaponControllerIC*>(
                     father->getComponent("WeaponControllerIC")))
                    ->getCurrentGun()
                    ->shoot();
            else
                (dynamic_cast<AutomaticEC*>(
                     father->getComponent("AutomaticEC")))
                    ->setShoot(true);
        }
    } else if (automatic && _event.type == SDL_MOUSEBUTTONUP) {
        if (_event.button.button == SDL_BUTTON_LEFT) {
            (dynamic_cast<AutomaticEC*>(father->getComponent("AutomaticEC")))
                ->setShoot(false);
        }
    } else if (_event.type == SDL_KEYDOWN) {
        if (_event.key.keysym.sym == SDLK_r) {
            (dynamic_cast<WeaponControllerIC*>(
                 father->getComponent("WeaponControllerIC")))
                ->getCurrentGun()
                ->reload();
        }
    } else if (_event.type == SDL_KEYDOWN) {
        if (_event.key.keysym.sym == SDLK_r) {
            // reload
        }
    }
}

// FACTORY INFRASTRUCTURE
class PlayerShotICFactory final : public ComponentFactory {
  public:
    PlayerShotICFactory() = default;

    Component* create(Entity* _father, Json::Value& _data,
                      Scene* scene) override {
        PlayerShotIC* playerShot = new PlayerShotIC();
        scene->getComponentsManager()->addIC(playerShot);

        playerShot->setFather(_father);
        playerShot->setScene(scene);

        return playerShot;
    };
};

REGISTER_FACTORY("PlayerShotIC", PlayerShotIC);
