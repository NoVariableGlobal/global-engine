#include "RangedEnemyBehaviourEC.h"
#include "ComponentsManager.h"
#include "EnemyBehaviourEC.h"
#include "FactoriesFactory.h"
#include "Factory.h"
#include "OgreRoot.h"
#include "PlayerMovementIC.h"
#include "RigidbodyPC.h"
#include "Scene.h"
#include "SpawnerBulletsC.h"
#include "TransformComponent.h"
#include "TridimensionalObjectRC.h"
#include <Entity.h>
#include <json.h>

RangedEnemyBehaviourEC::RangedEnemyBehaviourEC() : EnemyBehaviourEC() {}

RangedEnemyBehaviourEC::~RangedEnemyBehaviourEC() {}

void RangedEnemyBehaviourEC::checkEvent() {
    EnemyBehaviourEC::checkEvent();
    if (active) {
        // attack every attackCooldown seconds
        if (timeToAttack()) {
            shoot();
        }
    }
}

std::string RangedEnemyBehaviourEC::getWeaponEquipped() {
    return weaponEquipped;
}

int RangedEnemyBehaviourEC::getArcPellets() { return arcPellets; }

int RangedEnemyBehaviourEC::getArcAngleDistance() { return arcAngleDistance; }

int RangedEnemyBehaviourEC::getBulletSpeed() { return bulletSpeed; }

void RangedEnemyBehaviourEC::setWeaponEquipped(std::string _weaponEquipped) {
    weaponEquipped = _weaponEquipped;
}

void RangedEnemyBehaviourEC::setArcPellets(int _arcPellets) {
    arcPellets = _arcPellets;
}

void RangedEnemyBehaviourEC::setArcAngleDistance(int _arcAngleDistance) {
    arcAngleDistance = _arcAngleDistance;
}

void RangedEnemyBehaviourEC::setBulletSpeed(int _bulletSpeed) {
    bulletSpeed = _bulletSpeed;
}

void RangedEnemyBehaviourEC::shoot() {
    // Save original rotation
    Ogre::SceneNode* node = dynamic_cast<TridimensionalObjectRC*>(
                                father->getComponent("TridimensionalObjectRC"))
                                ->getSceneNode();

    // Orientate for the first pellet
    int firstPelletAngle = -arcAngleDistance * (arcPellets / 2);

    node->yaw(Ogre::Radian(Ogre::Degree(firstPelletAngle).valueRadians()));

    for (int i = 0; i < arcPellets; i++) {
        Entity* newBullet =
            dynamic_cast<SpawnerBulletsC*>(
                scene->getEntitybyId("GameManager")
                    ->getComponent("SpawnerBulletsC"))
                ->getBullet("EnemyBullet_" + weaponEquipped, "EnemyBullet");

        TransformComponent* bulletTransform = dynamic_cast<TransformComponent*>(
            newBullet->getComponent("TransformComponent"));

        TransformComponent* myTransform = dynamic_cast<TransformComponent*>(
            father->getComponent("TransformComponent"));

        bulletTransform->setPosition(myTransform->getPosition());
        bulletTransform->setOrientation(myTransform->getOrientation());

        RigidbodyPC* bulletRb =
            dynamic_cast<RigidbodyPC*>(newBullet->getComponent("RigidbodyPC"));

        Ogre::Quaternion quat = node->getOrientation();

        bulletRb->setLinearVelocity(-(quat * Ogre::Vector3::NEGATIVE_UNIT_Z) *
                                    bulletSpeed);
        bulletRb->setPosition(myTransform->getPosition() +
                              getDirectionToPlayer() * 2);

        // Rotate the node for the next bullet
        node->yaw(Ogre::Radian(Ogre::Degree(arcAngleDistance).valueRadians()));
    }
}

// FACTORY INFRASTRUCTURE
class RangedEnemyBehaviourECFactory final : public ComponentFactory {
  public:
    RangedEnemyBehaviourECFactory() = default;

    Component* create(Entity* _father, Json::Value& _data,
                      Scene* scene) override {
        RangedEnemyBehaviourEC* rangedEnemyBehaviour =
            new RangedEnemyBehaviourEC();
        scene->getComponentsManager()->addEC(rangedEnemyBehaviour);

        rangedEnemyBehaviour->setFather(_father);
        rangedEnemyBehaviour->setScene(scene);

        if (!_data["speed"].isDouble())
            throw std::exception("MeleeEnemyBehaviourEC: speed is not a float");
        rangedEnemyBehaviour->setSpeed(_data["speed"].asFloat());

        if (!_data["attack"].isInt())
            throw std::exception(
                "RangedMeleeEnemyBehaviourPC: attack is not an int");
        rangedEnemyBehaviour->setAttack(_data["attack"].asInt());

        if (!_data["attackCooldown"].isDouble())
            throw std::exception(
                "RangedEnemyBehaviourEC: attackCooldown is not a float");
        rangedEnemyBehaviour->setAttackCooldown(
            _data["attackCooldown"].asFloat());

        if (!_data["weaponEquipped"].isString())
            throw std::exception(
                "RangedEnemyBehaviourEC: weaponEquipped is not a string");
        rangedEnemyBehaviour->setWeaponEquipped(
            _data["weaponEquipped"].asString());

        if (!_data["arcPellets"].isInt())
            throw std::exception(
                "RangedMeleeEnemyBehaviourPC: arcPellets is not an int");
        rangedEnemyBehaviour->setArcPellets(_data["arcPellets"].asInt());

        if (!_data["arcAngleDistance"].isInt())
            throw std::exception(
                "RangedMeleeEnemyBehaviourPC: arcAngleDistance is not an int");
        rangedEnemyBehaviour->setArcAngleDistance(
            _data["arcAngleDistance"].asInt());

        if (!_data["bulletSpeed"].isInt())
            throw std::exception("RangedMeleeEnemyBehaviourPC: "
                                 "bulletSpeed is not an int");
        rangedEnemyBehaviour->setBulletSpeed(_data["bulletSpeed"].asInt());

        return rangedEnemyBehaviour;
    };
};

REGISTER_FACTORY("RangedEnemyBehaviourEC", RangedEnemyBehaviourEC);
