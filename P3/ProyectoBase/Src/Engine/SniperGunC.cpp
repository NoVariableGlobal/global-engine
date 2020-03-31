#include "SniperGunC.h"
#include "BulletC.h"
#include "ComponentsManager.h"
#include "Entity.h"
#include "FactoriesFactory.h"
#include "RigidbodyPC.h"
#include "Scene.h"
#include "SpawnerBulletsC.h"
#include "TransformComponent.h"
#include "TridimensionalObjectRC.h"

#include <OgreQuaternion.h>
#include <OgreSceneNode.h>
#include <json.h>

void SniperGunC::destroy() {
    setActive(false);
    scene->getComponentsManager()->eraseDC(this);
}

bool SniperGunC::shoot() {
    if (!canShoot())
        return false;

    if (!getInfiniteAmmo())
        _bulletchamber--;

    auto spawner = reinterpret_cast<SpawnerBulletsC*>(
        scene->getEntitybyId("GameManager")->getComponent("SpawnerBulletsC"));
    Entity* newBullet = spawner->getBullet("SniperBullet", _myBulletTag);

    BulletC* bullet =
        dynamic_cast<BulletC*>(newBullet->getComponent("SniperBulletC"));

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
    return true;
}

// FACTORY INFRASTRUCTURE
SniperGunCFactory::SniperGunCFactory() = default;

    Component* SniperGunCFactory::create(Entity* _father, Json::Value& _data,
                      Scene* _scene) {

        SniperGunC* sniper = new SniperGunC();

        _scene->getComponentsManager()->addDC(sniper);
        sniper->setFather(_father);
        sniper->setScene(_scene);

        if (!_data["bulletTag"].isString())
            throw std::exception("SniperGunC: bulletTag is not a string");
        sniper->setBulletTag(_data["bulletTag"].asString());

        if (!_data["bulletchamberMax"].isInt())
            throw std::exception("SniperGunC: bulletchamberMax is not an int");
        sniper->setbulletchamber(_data["bulletchamberMax"].asInt());

        if (!_data["munition"].isInt())
            throw std::exception("SniperGunC: munition is not an int");
        sniper->setmunition(_data["munition"].asInt());

        if (!_data["bulletDamage"].isDouble())
            throw std::exception("ShotgunC: bulletDamage is not a double");
        sniper->setbulletdamage(_data["bulletDamage"].asDouble());

        if (!_data["bulletSpeed"].isDouble())
            throw std::exception("ShotgunC: bulletSpeed is not a double");
        sniper->setbulletspeed(_data["bulletSpeed"].asDouble());

        if (!_data["cadence"].isDouble())
            throw std::exception("SniperGunC: cadence is not an int");
        sniper->setcadence(_data["cadence"].asFloat());

        if (!_data["instakill"].isBool())
            throw std::exception("SniperGunC: instakill is not an bool");
        sniper->setInstakill(_data["instakill"].asBool());

        sniper->setautomatic(false);

        sniper->setTransform(dynamic_cast<TransformComponent*>(
            _father->getComponent("TransformComponent")));

        return sniper;
    };
DEFINE_FACTORY(SniperGunC);