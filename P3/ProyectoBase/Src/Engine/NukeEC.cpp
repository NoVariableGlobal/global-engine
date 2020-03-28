#include "NukeEC.h"

#include "ComponentsManager.h"
#include "Entity.h"
#include "FactoriesFactory.h"
#include "Factory.h"
#include "LifeC.h"
#include "OgreVector3.h"
#include "RigidbodyPC.h"
#include "Scene.h"
#include "TransformComponent.h"
#include "TridimensionalObjectRC.h"

#include <iostream>
#include <json.h>

NukeEC::NukeEC() {}
NukeEC::~NukeEC() {}

void NukeEC::destroy() {
    setActive(false);
    scene->getComponentsManager()->eraseEC(this);
}

void NukeEC::checkEvent() {
    PowerUpEC::checkEvent();

    if (!picked && getCollisionWithPlayer()) {
        picked = true;

        std::vector<Entity*> enemies = scene->getEntitiesbyTag("Enemy");

        for (auto it : enemies) {
            scene->deleteEntity(it);
        }

        scene->deleteEntity(father);
    }
    if (!picked) { // delete item when the effect has passed
        if (timeDisappear()) {
            scene->deleteEntity(father);
        }
    }
}

// FACTORY INFRASTRUCTURE
class NukeECFactory final : public ComponentFactory {
  public:
    NukeECFactory() = default;

    Component* create(Entity* _father, Json::Value& _data,
                      Scene* scene) override {
        NukeEC* nukeEC = new NukeEC();
        scene->getComponentsManager()->addEC(nukeEC);
        nukeEC->setFather(_father);
        nukeEC->setScene(scene);

        if (!_data["time"].isDouble())
            throw std::exception("NukeEC: time is not a double");
        nukeEC->setDuration(_data["time"].asDouble());

        nukeEC->setActive(true);

        return nukeEC;
    };
};

REGISTER_FACTORY("NukeEC", NukeEC);
