#include "DestroyAfterSecsEC.h"
#include "ComponentsManager.h"
#include "Entity.h"
#include "FactoriesFactory.h"
#include "Factory.h"
#include "Scene.h"

#include <iostream>
#include <time.h>
#include <value.h>

void DestroyAfterSecsEC::checkEvent() {
    if (firstTime) {
        firstTime = false;
        creationTime = clock() / static_cast<float>(CLOCKS_PER_SEC);
    }

    float seconds = clock() / static_cast<float>(CLOCKS_PER_SEC);
    if (seconds - creationTime >= lifeTime) {
        scene->deleteEntity(father);
    }
}

void DestroyAfterSecsEC::setLifeTime(int n) { lifeTime = n; }

// FACTORY INFRASTRUCTURE
class DestroyAfterSecsECFactory final : public ComponentFactory {
  public:
    DestroyAfterSecsECFactory() = default;

    Component* create(Entity* _father, Json::Value& _data,
                      Scene* _scene) override {
        DestroyAfterSecsEC* destroyAfterSecsEC = new DestroyAfterSecsEC();

        destroyAfterSecsEC->setFather(_father);
        destroyAfterSecsEC->setScene(_scene);
        _scene->getComponentsManager()->addEC(destroyAfterSecsEC);

        if (!_data["lifeTime"].isDouble())
            throw std::exception(
                "DestroyAfterSecsEC: lifeTime is not a double");
        destroyAfterSecsEC->setLifeTime(_data["lifeTime"].asDouble());

        destroyAfterSecsEC->setActive(true);

        return destroyAfterSecsEC;
    };
};

REGISTER_FACTORY("DestroyAfterSecsEC", DestroyAfterSecsEC);