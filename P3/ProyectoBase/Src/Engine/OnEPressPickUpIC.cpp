#include "OnEPressPickUpIC.h"
#include "ComponentsManager.h"
#include "Entity.h"
#include "FactoriesFactory.h"
#include "Factory.h"
#include "GunC.h"
#include "PowerUpC.h"
#include "RigidbodyPC.h"
#include "Scene.h"
#include "WeaponControllerIC.h"

#include <iostream>
#include <json.h>

void OnEPressPickUpIC::destroyMyself() {
    scene->getComponentsManager()->eraseIC(this);
}

void OnEPressPickUpIC::handleInput(const SDL_Event& _event) {
    rb = dynamic_cast<RigidbodyPC*>(father->getComponent("RigidbodyPC"));
    if (rb->collidesWith("Simbad")) {
        // TODO: Mostrar un icono con la "E" cuando haya interfaz

        if (_event.type == SDL_KEYDOWN && _event.key.keysym.sym == SDLK_e) {
            dynamic_cast<PowerUpC*>(father->getComponent(objectName))
                ->onPickUp();
        }
    }
}

void OnEPressPickUpIC::setObjectName(std::string _name) { objectName = _name; }

// FACTORY INFRASTRUCTURE
class OnEPressPickUpICFactory : public ComponentFactory {
  public:
    OnEPressPickUpICFactory() = default;
    virtual Component* create(Entity* _father, Json::Value& _data,
                              Scene* scene) {
        // Create the component
        OnEPressPickUpIC* onEPressPickUpIC = new OnEPressPickUpIC();
        scene->getComponentsManager()->addIC(onEPressPickUpIC);

        onEPressPickUpIC->setObjectName(_data["objectName"].asString());

        // Set the component's father as the entity it was instanced for
        onEPressPickUpIC->setFather(_father);

        return onEPressPickUpIC;
    };
};

REGISTER_FACTORY("OnEPressPickUpIC", OnEPressPickUpIC);
