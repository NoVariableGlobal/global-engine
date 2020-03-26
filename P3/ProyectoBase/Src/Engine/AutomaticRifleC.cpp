#include "AutomaticRifleC.h"
#include "ComponentsManager.h"
#include "Entity.h"
#include "FactoriesFactory.h"
#include "Factory.h"
#include "Ogre.h"
#include "OgreQuaternion.h"
#include "OgreSceneNode.h"
#include "OgreVector3.h"
#include "RigidbodyPC.h"
#include "Scene.h"
#include "SpawnerBulletsC.h"
#include "TransformComponent.h"
#include "TridimensionalObjectRC.h"
#include <json.h>

AutomaticRifleC::AutomaticRifleC() : GunC() {}

AutomaticRifleC::~AutomaticRifleC() {}

void AutomaticRifleC::destroy () {
    scene->getComponentsManager()->eraseDC(this);
}

bool AutomaticRifleC::shoot() {
    if (_bulletchamber > 0) {
        _bulletchamber--;
        Entity* newBullet = dynamic_cast<SpawnerBulletsC*>(
                                scene->getEntitybyId("GameManager")
                                    ->getComponent("SpawnerBulletsC"))
                                ->getBullet("AutomaticRifleBullet");

        TransformComponent* bulletTransform = dynamic_cast<TransformComponent*>(
            newBullet->getComponent("TransformComponent"));

        Ogre::Quaternion quat =
            dynamic_cast<TridimensionalObjectRC*>(
                father->getComponent("TridimensionalObjectRC"))
                ->getSceneNode()
                ->getOrientation();

        bulletTransform->setPosition(myTransform->getPosition() +
                                     (quat * Ogre::Vector3::UNIT_Z) * 10);
        bulletTransform->setOrientation(myTransform->getOrientation());

        RigidbodyPC* bulletRb =
            dynamic_cast<RigidbodyPC*>(newBullet->getComponent("RigidbodyPC"));

        bulletRb->setLinearVelocity((quat * Ogre::Vector3::UNIT_Z) * 50);
        bulletRb->setPosition(bulletTransform->getPosition());

    } else
        return false;
}

// FACTORY INFRASTRUCTURE
class AutomaticRifleCFactory final : public ComponentFactory {
  public:
    AutomaticRifleCFactory() = default;

    Component* create(Entity* _father, Json::Value& _data,
                      Scene* _scene) override {

        AutomaticRifleC* automaticRifle = new AutomaticRifleC();

        _scene->getComponentsManager()->addDC(automaticRifle);
        automaticRifle->setFather(_father);
        automaticRifle->setScene(_scene);

        if (!_data["bulletchamberMax"].isInt())
            throw std::exception("ShotgunC: bulletchamberMax is not an int");
        automaticRifle->setbulletchamber(_data["bulletchamberMax"].asInt());

        if (!_data["munition"].isInt())
            throw std::exception("ShotgunC: munition is not an int");
        automaticRifle->setmunition(_data["munition"].asInt());

        if (!_data["cadence"].isDouble())
            throw std::exception("ShotgunC: cadence is not an int");
        automaticRifle->setcadence(_data["cadence"].asFloat());

        if (!_data["damage"].isDouble())
            throw std::exception("ShotgunC: damage is not an int");
        automaticRifle->setdamage(_data["damage"].asFloat());

        if (!_data["semiautomatic"].isBool())
            throw std::exception("ShotgunC: semiautomatic is not an bool");
        automaticRifle->setsemiautomatic(_data["semiautomatic"].asBool());

        automaticRifle->setTransform(dynamic_cast<TransformComponent*>(
            _father->getComponent("TransformComponent")));

        return automaticRifle;
    };
};

REGISTER_FACTORY("AutomaticRifleC", AutomaticRifleC);