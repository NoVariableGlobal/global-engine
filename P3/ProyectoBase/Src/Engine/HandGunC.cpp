#include "HandGunC.h"
#include "BulletC.h"
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

HandGunC::HandGunC() : GunC() {}

HandGunC::~HandGunC() {}

void HandGunC::destroy() {
    setActive(false);
    scene->getComponentsManager()->eraseDC(this);
}

bool HandGunC::shoot() {
    if (!canShoot())
        return false;

    if (!getInfiniteAmmo())
        _bulletchamber--;

    auto spawner = reinterpret_cast<SpawnerBulletsC*>(
        scene->getEntitybyId("GameManager")->getComponent("SpawnerBulletsC"));
    Entity* newBullet = spawner->getBullet("HandgunBullet", _myBulletTag);

    BulletC* bullet =
        dynamic_cast<BulletC*>(newBullet->getComponent("BulletC"));

    bullet->setDamage(getCalculatedDamage());

    TransformComponent* bulletTransform = dynamic_cast<TransformComponent*>(
        newBullet->getComponent("TransformComponent"));

    Ogre::Quaternion quat = dynamic_cast<TridimensionalObjectRC*>(
                                father->getComponent("TridimensionalObjectRC"))
                                ->getSceneNode()
                                ->getOrientation();

    bulletTransform->setPosition(myTransform->getPosition() +
                                 (quat * Ogre::Vector3::UNIT_Z) * 10);
    bulletTransform->setOrientation(myTransform->getOrientation());

    RigidbodyPC* bulletRb =
        dynamic_cast<RigidbodyPC*>(newBullet->getComponent("RigidbodyPC"));

    bulletRb->setLinearVelocity((quat * Ogre::Vector3::UNIT_Z) * _bulletSpeed);
    bulletRb->setPosition(bulletTransform->getPosition());
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

        if (!_data["bulletTag"].isString())
            throw std::exception("ShotgunC: bulletTag is not a string");
        hg->setBulletTag(_data["bulletTag"].asString());

        if (!_data["bulletchamberMax"].isInt())
            throw std::exception("HandGunC: bulletchamberMax is not an int");
        hg->setbulletchamber(_data["bulletchamberMax"].asInt());

        if (!_data["munition"].isInt())
            throw std::exception("HandGunC: munition is not an int");
        hg->setmunition(_data["munition"].asInt());

        if (!_data["bulletDamage"].isDouble())
            throw std::exception("ShotgunC: bulletDamage is not a double");
        hg->setbulletdamage(_data["bulletDamage"].asDouble());

        if (!_data["bulletSpeed"].isDouble())
            throw std::exception("ShotgunC: bulletSpeed is not a double");
        hg->setbulletspeed(_data["bulletSpeed"].asDouble());

        if (!_data["cadence"].isDouble())
            throw std::exception("HandGunC: cadence is not an int");
        hg->setcadence(_data["cadence"].asFloat());

        if (!_data["automatic"].isBool())
            throw std::exception("HandGunC: semiautomatic is not an bool");
        hg->setautomatic(_data["automatic"].asBool());

        if (!_data["instakill"].isBool())
            throw std::exception("HandGunC: instakill is not an bool");
        hg->setInstakill(_data["instakill"].asBool());

        hg->setTransform(dynamic_cast<TransformComponent*>(
            _father->getComponent("TransformComponent")));

        return hg;
    };
};

REGISTER_FACTORY("HandGunC", HandGunC);
