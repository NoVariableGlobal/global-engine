#include "PlayerShotIC.h"
#include "ComponentsManager.h"
#include "Entity.h"
#include "FactoriesFactory.h"
#include "GunC.h"
#include "OgreRoot.h"
#include "Scene.h"
#include "WeaponControllerIC.h"
#include <json.h>

#include <iostream>

PlayerShotIC::PlayerShotIC() {}

PlayerShotIC::~PlayerShotIC() {}

void PlayerShotIC::destroy() {
    setActive(false);
    scene->getComponentsManager()->eraseIC(this);
}

void PlayerShotIC::handleInput(const SDL_Event& _event) {
    if (_event.type == SDL_MOUSEBUTTONDOWN) {
        if (_event.button.button == SDL_BUTTON_LEFT) {
            // TODO: Tell gun component to fire a shot
            (dynamic_cast<WeaponControllerIC*>(
                 father->getComponent("WeaponControllerIC")))
                ->getCurrentGun()
                ->shoot();
        }
    } else if (_event.type == SDL_KEYDOWN) {
        if (_event.key.keysym.sym == SDLK_r) {
            (dynamic_cast<WeaponControllerIC*>(
                 father->getComponent("WeaponControllerIC")))
                ->getCurrentGun()
                ->reload();
        }
    }
}

// FACTORY INFRASTRUCTURE
PlayerShotICFactory::PlayerShotICFactory() = default;

Component* PlayerShotICFactory::create(Entity* _father, Json::Value& _data,
                                       Scene* scene)  {
    PlayerShotIC* playerShot = new PlayerShotIC();
    scene->getComponentsManager()->addIC(playerShot);

    playerShot->setFather(_father);
    playerShot->setScene(scene);

    return playerShot;
};

DEFINE_FACTORY(PlayerShotIC);
