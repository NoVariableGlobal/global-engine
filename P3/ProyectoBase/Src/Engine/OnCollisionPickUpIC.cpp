#include "OnCollisionPickUpIC.h"
#include "ComponentsManager.h"
#include "Entity.h"
#include "FactoriesFactory.h"
#include "Factory.h"
#include "GunC.h"
#include "PowerUpEC.h"
#include "RigidbodyPC.h"
#include "Scene.h"

#include <iostream>
#include <json.h>

OnCollisionPickUpIC::OnCollisionPickUpIC() {
    rb = dynamic_cast<RigidbodyPC*>(father->getComponent("RigidbodyPC"));
}

void OnCollisionPickUpIC::handleInput(const SDL_Event& _event) {
    if (rb->collidesWith("Simbad")) {
        dynamic_cast<PowerUpEC*>(father->getComponent(objectName))->onPickUp();
    }
}

void OnCollisionPickUpIC::setObjectName(std::string _name) {
    objectName = _name;
}

// FACTORY INFRASTRUCTURE
class OnCollisionPickUpICFactory : public ComponentFactory {
  public:
    OnCollisionPickUpICFactory() = default;
    virtual Component* create(Entity* _father, Json::Value& _data,
                              Scene* scene) {
        // Create the component
        OnCollisionPickUpIC* onCollisionPickUpIC = new OnCollisionPickUpIC();
        scene->getComponentsManager()->addIC(onCollisionPickUpIC);

        onCollisionPickUpIC->setObjectName(_data["objectName"].asString());

        // Set the component's father as the entity it was instanced for
        onCollisionPickUpIC->setFather(_father);

        return onCollisionPickUpIC;
    };
};

REGISTER_FACTORY("OnCollisionPickUpIC", OnCollisionPickUpIC);