#include "PlayerShotIC.h"
#include "ComponentsManager.h"
#include "FactoriesFactory.h"
#include "Factory.h"
#include "Scene.h"
#include "WeaponControllerIC.h"
#include "OgreRoot.h"
#include "Entity.h"
#include "GunC.h"
#include <json.h>
#include "SemiAutomaticEC.h"
#include <iostream>

PlayerShotIC::PlayerShotIC() {}

PlayerShotIC::~PlayerShotIC() {}

void PlayerShotIC::destroy() {
    setActive(false);
    scene->getComponentsManager()->eraseIC(this);
}

void PlayerShotIC::handleInput(const SDL_Event& _event) {
    bool automatic = (dynamic_cast<WeaponControllerIC*>(
                          father->getComponent("WeaponControllerIC")))
                         ->getCurrentGun()
                         ->getsemiautomatic();
    if (_event.type == SDL_MOUSEBUTTONDOWN) {
        if (_event.button.button == SDL_BUTTON_LEFT) {
            // TODO: Tell gun component to fire a shot
            if (!automatic)
                (dynamic_cast<WeaponControllerIC*>(
                     father->getComponent("WeaponControllerIC")))
                    ->getCurrentGun()
                    ->shoot();
            else
                (dynamic_cast<SemiAutomaticEC*>(
                     father->getComponent("SemiAutomaticEC")))
                    ->setShoot(true);
        }
    } else if (_event.type == SDL_MOUSEBUTTONUP) {
        if (_event.button.button == SDL_BUTTON_LEFT) {
            (dynamic_cast<SemiAutomaticEC*>(
                 father->getComponent("SemiAutomaticEC")))
                ->setShoot(false);
        }
    }
	else if (_event.type == SDL_KEYDOWN) {
        if (_event.key.keysym.sym == SDLK_r) {
            (dynamic_cast<WeaponControllerIC*>(father->getComponent("WeaponControllerIC")))->getCurrentGun()->reload();
        }
    } else if (_event.type == SDL_KEYDOWN) {
        if (_event.key.keysym.sym == SDLK_r) {
            //reload
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
