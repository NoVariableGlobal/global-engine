#include "SniperGunC.h"
#include "Scene.h"
#include "ComponentsManager.h"
#include "SpawnerBulletsC.h"
#include "Entity.h"
#include  <OgreQuaternion.h>
#include "TridimensionalObjectRC.h"
#include "TransformComponent.h"
#include <OgreSceneNode.h>
#include "RigidbodyPC.h"
#include <json.h>
#include "Factory.h"
#include "FactoriesFactory.h"

void SniperGunC::destroy() {
    setActive(false);
    scene->getComponentsManager()->eraseDC(this);
}


bool SniperGunC::shoot() {
    if (_bulletchamber == 0)
        return false;
    
    _bulletchamber--;

    Entity* newBullet =
        dynamic_cast<SpawnerBulletsC*>(scene->getEntitybyId("GameManager")
                                           ->getComponent("SpawnerBulletsC"))
            ->getBullet("SniperBullet", _myBulletTag);

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

    bulletRb->setLinearVelocity((quat * Ogre::Vector3::UNIT_Z) * 100);
    bulletRb->setPosition(bulletTransform->getPosition());
    return true;
}

// FACTORY INFRASTRUCTURE
class SniperGunCFactory final : public ComponentFactory {
  public:
    SniperGunCFactory() = default;

    Component* create(Entity* _father, Json::Value& _data,
                      Scene* _scene) override {

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

        if (!_data["cadence"].isDouble())
            throw std::exception("SniperGunC: cadence is not an int");
        sniper->setcadence(_data["cadence"].asFloat());

        sniper->setautomatic(false);

        sniper->setTransform(dynamic_cast<TransformComponent*>(
            _father->getComponent("TransformComponent")));

        return sniper;
    };
};

REGISTER_FACTORY("SniperGunC", SniperGunC);