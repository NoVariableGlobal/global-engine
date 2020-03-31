#include "AutomaticRifleC.h"
#include "BulletC.h"
#include "ComponentsManager.h"
#include "Entity.h"
#include "FactoriesFactory.h"
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

void AutomaticRifleC::destroy() {
    setActive(false);
    scene->getComponentsManager()->eraseDC(this);
}

bool AutomaticRifleC::shoot() {
    if (!canShoot())
        return false;

    if (!getInfiniteAmmo())
        _bulletchamber--;

    auto spawner = reinterpret_cast<SpawnerBulletsC*>(
        scene->getEntitybyId("GameManager")->getComponent("SpawnerBulletsC"));
    Entity* newBullet =
        spawner->getBullet("AutomaticRifleBullet", _myBulletTag);

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
AutomaticRifleCFactory::AutomaticRifleCFactory() = default;

    Component* AutomaticRifleCFactory::create(Entity* _father, Json::Value& _data,
                      Scene* _scene)  {

        AutomaticRifleC* automaticRifle = new AutomaticRifleC();

        _scene->getComponentsManager()->addDC(automaticRifle);
        automaticRifle->setFather(_father);
        automaticRifle->setScene(_scene);

        if (!_data["bulletTag"].isString())
            throw std::exception("AutomaticRifleC: bulletTag is not a string");
        automaticRifle->setBulletTag(_data["bulletTag"].asString());

        if (!_data["bulletchamberMax"].isInt())
            throw std::exception(
                "AutomaticRifleC: bulletchamberMax is not an int");
        automaticRifle->setbulletchamber(_data["bulletchamberMax"].asInt());

        if (!_data["munition"].isInt())
            throw std::exception("AutomaticRifleC: munition is not an int");
        automaticRifle->setmunition(_data["munition"].asInt());

        if (!_data["bulletDamage"].isDouble())
            throw std::exception("ShotgunC: bulletDamage is not a double");
        automaticRifle->setbulletdamage(_data["bulletDamage"].asDouble());

        if (!_data["bulletSpeed"].isDouble())
            throw std::exception("ShotgunC: bulletSpeed is not a double");
        automaticRifle->setbulletspeed(_data["bulletSpeed"].asDouble());

        if (!_data["cadence"].isDouble())
            throw std::exception("AutomaticRifleC: cadence is not an int");
        automaticRifle->setcadence(_data["cadence"].asFloat());

        if (!_data["automatic"].isBool())
            throw std::exception("AutomaticRifleC: automatic is not an bool");
        automaticRifle->setautomatic(_data["automatic"].asBool());

        if (!_data["instakill"].isBool())
            throw std::exception("AutomaticRifleC: instakill is not an bool");
        automaticRifle->setInstakill(_data["instakill"].asBool());

        automaticRifle->setTransform(dynamic_cast<TransformComponent*>(
            _father->getComponent("TransformComponent")));

        return automaticRifle;
    };

DEFINE_FACTORY(AutomaticRifleC);