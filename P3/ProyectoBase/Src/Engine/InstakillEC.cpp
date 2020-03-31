#include "InstakillEC.h"
#include "AutomaticRifleC.h"
#include "ComponentsManager.h"
#include "Entity.h"
#include "FactoriesFactory.h"
#include "Factory.h"
#include "GunC.h"
#include "HandGunC.h"
#include "Scene.h"
#include "ShotgunC.h"
#include "SniperGunC.h"
#include <json.h>
#include <value.h>

void InstakillEC::setEffect(bool effect) {
    Entity* player = scene->getEntitybyId("Player");
    reinterpret_cast<AutomaticRifleC*>(player->getComponent("AutomaticRifleC"))
        ->setInstakill(effect);
    reinterpret_cast<HandGunC*>(player->getComponent("HandGunC"))
        ->setInstakill(effect);
    reinterpret_cast<ShotgunC*>(player->getComponent("ShotgunC"))
        ->setInstakill(effect);
    reinterpret_cast<SniperGunC*>(player->getComponent("SniperGunC"))
        ->setInstakill(effect);
}

std::string InstakillEC::getName() { return "InstakillEC"; }

// FACTORY INFRASTRUCTURE
class InstakillECFactory final : public ComponentFactory {
  public:
    InstakillECFactory() = default;

    Component* create(Entity* _father, Json::Value& _data,
                      Scene* scene) override {
        InstakillEC* instakill = new InstakillEC();

        instakill->setFather(_father);
        instakill->setScene(scene);
        scene->getComponentsManager()->addEC(instakill);

        if (!_data["time"].isDouble())
            throw std::exception("InstakillEC: time is not a double");
        instakill->setDuration(_data["time"].asDouble());

        if (!_data["timeEffect"].isDouble())
            throw std::exception("InstakillEC: timeEffect is not a double");
        instakill->setDuration(_data["timeEffect"].asDouble());

        instakill->setActive(true);

        return instakill;
    };
};

REGISTER_FACTORY("InstakillEC", InstakillEC);
