#include "PlayerShotIC.h"
#include "ComponentsManager.h"
#include "FactoriesFactory.h"
#include "Factory.h"
#include "Scene.h"

#include "OgreRoot.h"

#include <json.h>

#include <iostream>

PlayerShotIC::PlayerShotIC() {}

PlayerShotIC::~PlayerShotIC() {}

void PlayerShotIC::handleInput(const SDL_Event& _event) {
    if (_event.type == SDL_MOUSEBUTTONDOWN) {
        if (_event.button.button == SDL_BUTTON_LEFT) {
            // TODO: Tell gun component to fire a shot
            std::cout << '\n' << "PIUM PIUM !!" << '\n';
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
