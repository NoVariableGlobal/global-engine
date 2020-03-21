#include "HandGunC.h"
#include "FactoriesFactory.h"
#include "Factory.h"
#include "Scene.h"
#include "ComponentsManager.h"
#include <json.h>

HandGunC::HandGunC() : GunC() {}

HandGunC::~HandGunC() {}

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

        return hg;
    };
};

REGISTER_FACTORY("HandGunC", HandGunC);