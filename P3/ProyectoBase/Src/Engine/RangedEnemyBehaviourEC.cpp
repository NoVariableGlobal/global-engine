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

    // attack every attackCooldown seconds
    if (timeToAttack()) {
        // shoot bullets in different modes depending on weapon equipped
        if (weaponEquipped == "handgun" || weaponEquipped == "rifle")
			shootStraight();
        // TO DO: add more weapon types
    }
}

std::string RangedEnemyBehaviourEC::getWeaponEquipped() {
    return weaponEquipped;
}

void RangedEnemyBehaviourEC::setWeaponEquipped(std::string _weaponEquipped) {
    weaponEquipped = _weaponEquipped;
}

void RangedEnemyBehaviourEC::shootStraight() {
    Entity* newBullet =
        dynamic_cast<SpawnerBulletsC*>(scene->getEntitybyId("GameManager")
                                           ->getComponent("SpawnerBulletsC"))
            ->getBullet("EnemyBullet_" + weaponEquipped, "EnemyBullet");

    TransformComponent* bulletTransform = dynamic_cast<TransformComponent*>(
        newBullet->getComponent("TransformComponent"));

    Ogre::Quaternion quat = dynamic_cast<TridimensionalObjectRC*>(
                                father->getComponent("TridimensionalObjectRC"))
                                ->getSceneNode()
                                ->getOrientation();

    TransformComponent* myTransform = dynamic_cast<TransformComponent*>(
        father->getComponent("TransformComponent"));

    bulletTransform->setPosition(myTransform->getPosition() +
                                 (quat * Ogre::Vector3::UNIT_Z) * 10);
    bulletTransform->setOrientation(myTransform->getOrientation());

    RigidbodyPC* bulletRb =
        dynamic_cast<RigidbodyPC*>(newBullet->getComponent("RigidbodyPC"));

    bulletRb->setLinearVelocity(getDirectionToPlayer() * 50);
    bulletRb->setPosition(bulletTransform->getPosition());
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

        if (!_data["playerSpeedPercentage"].asFloat())
            throw std::exception(
                "RangedEnemyBehaviourEC: playerSpeedPercentage is not a float");
        rangedEnemyBehaviour->setPlayerSpeedPercentage(
            _data["playerSpeedPercentage"].asFloat());

        PlayerMovementIC* playerMovement = dynamic_cast<PlayerMovementIC*>(
            scene->getEntitybyId("Player")->getComponent("PlayerMovementIC"));

        // enemy speed depends on player speed and player speed percentage
        rangedEnemyBehaviour->setSpeed(
            playerMovement->getMovementSpeed() *
            rangedEnemyBehaviour->getPlayerSpeedPercentage());

        if (!_data["attack"].asInt())
            throw std::exception(
                "RangedMeleeEnemyBehaviourPC: attack is not an int");
        rangedEnemyBehaviour->setAttack(_data["attack"].asInt());

        if (!_data["attackCooldown"].asFloat())
            throw std::exception(
                "RangedEnemyBehaviourEC: attackCooldown is not a float");
        rangedEnemyBehaviour->setAttackCooldown(
            _data["attackCooldown"].asFloat());

        if (!_data["weaponEquipped"].isString())
            throw std::exception(
                "RangedEnemyBehaviourEC: weaponEquipped is not a string");
        rangedEnemyBehaviour->setWeaponEquipped(
            _data["weaponEquipped"].asString());

        return rangedEnemyBehaviour;
    };
};

REGISTER_FACTORY("RangedEnemyBehaviourEC", RangedEnemyBehaviourEC);
