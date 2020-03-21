#include "HandGunC.h"
#include "FactoriesFactory.h"
#include "Factory.h"
#include "SpawnerBulletsC.h"
#include "Scene.h"
#include "Entity.h"
#include "ComponentsManager.h"
#include "TransformComponent.h"
#include <json.h>

HandGunC::HandGunC() : GunC() {}

HandGunC::~HandGunC() {}

bool GunC::shoot() {
    if (_bulletchamber > 0) {
        _bulletchamber--;
        Entity* newBullet = dynamic_cast<SpawnerBulletsC*>(
                                scene->getEntitybyId("GameManager")
                                    ->getComponent("SpawnerBulletsC"))
                                ->getBullet("HandgunBullet");

       TransformComponent* bulletTransform = dynamic_cast<TransformComponent*>(
            newBullet->getComponent("TransformComponent"));

       bulletTransform->setPosition(myTransform->getPosition());
       bulletTransform->setOrientation(myTransform->getOrientation());

    } else
        return false;
}

// FACTORY INFRASTRUCTURE
class HandGunCFactory final : public ComponentFactory {
  public:
    HandGunCFactory() = default;

    Component* create(Entity* _father, Json::Value& _data,
                      Scene* scene) override {

        HandGunC* hg = new HandGunC();

        scene->getComponentsManager()->addDC(hg);

        if (!_data["bulletchamberMax"].isInt())
            throw std::exception("HandGunC: bulletchamberMax is not an int");
        hg->setbulletchamber(_data["bulletchamberMax"].asInt());

        if (!_data["munition"].isInt())
            throw std::exception("HandGunC: munition is not an int");
        hg->setbulletchamber(_data["munition"].asInt());

        if (!_data["cadence"].asFloat())
            throw std::exception("HandGunC: cadence is not an int");
        hg->setbulletchamber(_data["cadence"].asFloat());

        if (!_data["damage"].asFloat())
            throw std::exception("HandGunC: damage is not an int");
        hg->setbulletchamber(_data["damage"].asFloat());

        if (!_data["semiautomatic"].asBool())
            throw std::exception("HandGunC: semiautomatic is not an int");
        hg->setbulletchamber(_data["semiautomatic"].asFloat());

        hg->setFather(_father);
        hg->setScene(scene);
        hg->setTransform(dynamic_cast<TransformComponent*>(_father->getComponent("TransformComponent")));

        return hg;
    };
};

REGISTER_FACTORY("HandGunC", HandGunC);