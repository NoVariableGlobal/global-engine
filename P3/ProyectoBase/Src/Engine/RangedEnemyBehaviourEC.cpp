#include "RangedEnemyBehaviourEC.h"
#include "ComponentsManager.h"
#include "EnemyBehaviourEC.h"
#include "FactoriesFactory.h"
#include "Factory.h"
#include "LifeC.h"
#include "OgreRoot.h"
#include "PlayerMovementIC.h"
#include "Scene.h"
#include <Entity.h>
#include <json.h>

RangedEnemyBehaviourEC::RangedEnemyBehaviourEC() : EnemyBehaviourEC() {}

RangedEnemyBehaviourEC::~RangedEnemyBehaviourEC() {}

void RangedEnemyBehaviourEC::checkEvent() {
    EnemyBehaviourEC::checkEvent();

	// attack every attackCooldown seconds
	if (timeToAttack())
     {
		// if enemy is colliding with player
        if (getCollisionWithPlayer())
         {
            // attack player
            LifeC* playerHealth = dynamic_cast<LifeC*>(
                scene->getEntitybyId("Player")->getComponent("LifeC"));
            playerHealth->doDamage(getAttack());
        }
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
            throw std::exception("RangedMeleeEnemyBehaviourPC: attack is not an int");
        rangedEnemyBehaviour->setAttack(_data["attack"].asInt());

        if (!_data["attackCooldown"].asFloat())
            throw std::exception(
                "RangedEnemyBehaviourEC: attackCooldown is not a float");
        rangedEnemyBehaviour->setAttackCooldown(
            _data["attackCooldown"].asFloat());

        return rangedEnemyBehaviour; 
    };
};

REGISTER_FACTORY("RangedEnemyBehaviourEC", RangedEnemyBehaviourEC);
