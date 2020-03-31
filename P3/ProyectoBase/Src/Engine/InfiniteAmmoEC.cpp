#include "InfiniteAmmoEC.h"
#include "AutomaticRifleC.h"
#include "ComponentsManager.h"
#include "Entity.h"
#include "FactoriesFactory.h"
#include "GunC.h"
#include "HandGunC.h"
#include "Scene.h"
#include "ShotgunC.h"
#include "SniperGunC.h"
#include <json.h>

void InfiniteAmmoEC::setEffect(bool value) {
    Entity* player = scene->getEntitybyId("Player");
    reinterpret_cast<AutomaticRifleC*>(player->getComponent("AutomaticRifleC"))
        ->setInfiniteAmmo(value);
    reinterpret_cast<HandGunC*>(player->getComponent("HandGunC"))
        ->setInfiniteAmmo(value);
    reinterpret_cast<ShotgunC*>(player->getComponent("ShotgunC"))
        ->setInfiniteAmmo(value);
    reinterpret_cast<SniperGunC*>(player->getComponent("SniperGunC"))
        ->setInfiniteAmmo(value);
}

std::string InfiniteAmmoEC::getName() { return "InfiniteAmmoEC"; }

// FACTORY INFRASTRUCTURE
InfiniteAmmoECFactory::InfiniteAmmoECFactory() = default;

    Component* InfiniteAmmoECFactory::create(Entity* _father, Json::Value& _data,
                      Scene* scene) {
        InfiniteAmmoEC* infiniteAmmo = new InfiniteAmmoEC();

        infiniteAmmo->setFather(_father);
        infiniteAmmo->setScene(scene);
        scene->getComponentsManager()->addEC(infiniteAmmo);

        if (!_data["time"].isDouble())
            throw std::exception("InfiniteAmmo: time is not a double");
        infiniteAmmo->setDuration(_data["time"].asDouble());

        if (!_data["timeEffect"].isDouble())
            throw std::exception("Shield: timeEffect is not a double");
        infiniteAmmo->setDuration(_data["timeEffect"].asDouble());

        infiniteAmmo->setActive(true);

        return infiniteAmmo;
    };

DEFINE_FACTORY(InfiniteAmmoEC);
