#include "InstakillEC.h"
#include "AutomaticRifleC.h"
#include "ComponentsManager.h"
#include "Entity.h"
#include "FactoriesFactory.h"
#include "Factory.h"
#include "GunC.h"
#include "HandGunC.h"
#include "LifeC.h"
#include "OgreVector3.h"
#include "RigidbodyPC.h"
#include "Scene.h"
#include "ShotgunC.h"
#include "SniperGunC.h"
#include "TransformComponent.h"
#include "TridimensionalObjectRC.h"
#include "WeaponControllerIC.h"
#include <iostream>
#include <json.h>

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

InstakillEC::InstakillEC() {}

InstakillEC::~InstakillEC() {}

void InstakillEC::checkEvent() {
    PowerUpEC::checkEvent();

    if (!picked && getCollisionWithPlayer()) {
        Entity* player = scene->getEntitybyId("Player");
        setEffect(true);
        picked = true;

        dynamic_cast<TridimensionalObjectRC*>(
            father->getComponent("TridimensionalObjectRC"))
            ->setActive(false);

        dynamic_cast<RigidbodyPC*>(father->getComponent("RigidbodyPC"))
            ->setActive(false);

        dynamic_cast<TransformComponent*>(
            father->getComponent("TransformComponent"))
            ->setActive(false);
    }
    if (!picked) { // delete item when the effect has passed
        if (timeDisappear()) {
            scene->deleteEntity(father);
        }
    } else if (timeDisappearEffect()) { // delete item when the effect has
                                        // passed
        setEffect(false);
        scene->deleteEntity(father);
    }
}

void InstakillEC::setTimeEffect(float _time) { timeEffect = _time; }

bool InstakillEC::timeDisappearEffect() {
    float seconds = clock() / static_cast<float>(CLOCKS_PER_SEC);

    if (!startPicked) {
        time = seconds;
        startPicked = true;
    }
    if (time + timeEffect <= seconds) {
        return true;
    }

    return false;
}

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
        instakill->setTimeEffect(_data["timeEffect"].asDouble());

        instakill->setActive(true);

        return instakill;
    };
};

REGISTER_FACTORY("InstakillEC", InstakillEC);
