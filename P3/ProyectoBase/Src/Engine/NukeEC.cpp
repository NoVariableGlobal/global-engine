#include "NukeEC.h"
#include "ComponentsManager.h"
#include "Entity.h"
#include "FactoriesFactory.h"
#include "Scene.h"
#include <json.h>

void NukeEC::onPick() {
    std::vector<Entity*> enemies = scene->getEntitiesbyTag("Enemy");

    for (auto it : enemies) {
        scene->deleteEntity(it);
    }
}

// FACTORY INFRASTRUCTURE
NukeECFactory::NukeECFactory() = default;

    Component* NukeECFactory::create(Entity* _father, Json::Value& _data,
                      Scene* scene) {
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

DEFINE_FACTORY(NukeEC);
