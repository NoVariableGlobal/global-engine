#include "HandGunC.h"
#include "FactoriesFactory.h"
#include "Factory.h"
#include "SpawnerBulletsC.h"
#include "Scene.h"
#include "Entity.h"
#include "ComponentsManager.h"
#include "TransformComponent.h"
#include "RigidbodyPC.h"
#include "TridimensionalObjectRC.h"
#include "OgreVector3.h"
#include "OgreSceneNode.h"
#include "OgreQuaternion.h"
#include "Ogre.h"
#include <json.h>

HandGunC::HandGunC() : GunC() {}

HandGunC::~HandGunC() {}

void HandGunC::destroyMyself() {
    setActive(false);
    scene->getComponentsManager()->eraseDC(this);
}

bool HandGunC::shoot() {
    if (_bulletchamber > 0) {
        _bulletchamber--;
        Entity* newBullet = dynamic_cast<SpawnerBulletsC*>(
                                scene->getEntitybyId("GameManager")
                                    ->getComponent("SpawnerBulletsC"))
                                ->getBullet("HandgunBullet");

       TransformComponent* bulletTransform = dynamic_cast<TransformComponent*>(
            newBullet->getComponent("TransformComponent"));

       Ogre::Quaternion quat =
           dynamic_cast<TridimensionalObjectRC*>(
               father->getComponent("TridimensionalObjectRC"))
               ->getSceneNode()
               ->getOrientation();

       bulletTransform->setPosition(myTransform->getPosition() +
                                    (quat * Ogre::Vector3::UNIT_Z) *10);
       bulletTransform->setOrientation(myTransform->getOrientation());

       RigidbodyPC* bulletRb = dynamic_cast<RigidbodyPC*>(
           newBullet->getComponent("RigidbodyPC"));



       bulletRb->setLinearVelocity((quat * Ogre::Vector3::UNIT_Z) * 50);
       bulletRb->setPosition(bulletTransform->getPosition());

    } else
        return false;
}

// FACTORY INFRASTRUCTURE
class HandGunCFactory final : public ComponentFactory {
  public:
    HandGunCFactory() = default;

    Component* create(Entity* _father, Json::Value& _data,
                      Scene* _scene) override {

        HandGunC* hg = new HandGunC();

        _scene->getComponentsManager()->addDC(hg);
        hg->setFather(_father);
        hg->setScene(_scene);

        if (!_data["bulletchamberMax"].isInt())
            throw std::exception("HandGunC: bulletchamberMax is not an int");
        hg->setbulletchamber(_data["bulletchamberMax"].asInt());

        if (!_data["munition"].isInt())
            throw std::exception("HandGunC: munition is not an int");
        hg->setmunition(_data["munition"].asInt());

        if (!_data["cadence"].isDouble())
            throw std::exception("HandGunC: cadence is not an int");
        hg->setcadence(_data["cadence"].asFloat());

        if (!_data["damage"].isDouble())
            throw std::exception("HandGunC: damage is not an int");
        hg->setdamage(_data["damage"].asFloat());

        if (!_data["semiautomatic"].isBool())
            throw std::exception("HandGunC: semiautomatic is not an bool");
        hg->setsemiautomatic(_data["semiautomatic"].asBool());


        hg->setTransform(dynamic_cast<TransformComponent*>(_father->getComponent("TransformComponent")));

        return hg;
    };
};

REGISTER_FACTORY("HandGunC", HandGunC);