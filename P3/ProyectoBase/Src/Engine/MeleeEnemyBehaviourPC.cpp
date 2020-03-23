#include "MeleeEnemyBehaviourPC.h"
#include "ComponentsManager.h"
#include "EnemyBehaviourPC.h"
#include "FactoriesFactory.h"
#include "Factory.h"
#include "LifeC.h"
#include "OgreRoot.h"
#include "PlayerMovementIC.h"
#include "Scene.h"
#include <Entity.h>
#include <json.h>

MeleeEnemyBehaviourPC::MeleeEnemyBehaviourPC() : EnemyBehaviourPC() {}

MeleeEnemyBehaviourPC::~MeleeEnemyBehaviourPC() {}

void MeleeEnemyBehaviourPC::checkEvent() {
    EnemyBehaviourPC::checkEvent();

    if (getCollisionWithPlayer()) {
		// attack every attackCooldown seconds
        if (timeToAttack()) {
            // attack player
            LifeC* playerHealth = dynamic_cast<LifeC*>(
                scene->getEntitybyId("Player")->getComponent("LifeC"));
            playerHealth->doDamage(getAttack());
        }
    }
}

// FACTORY INFRASTRUCTURE
class MeleeEnemyBehaviourPCFactory final : public ComponentFactory {
  public:
    MeleeEnemyBehaviourPCFactory() = default;

    Component* create(Entity* _father, Json::Value& _data,
                      Scene* scene) override {
        MeleeEnemyBehaviourPC* meleeEnemyBehaviour =
            new MeleeEnemyBehaviourPC();
        scene->getComponentsManager()->addEC(meleeEnemyBehaviour);

        meleeEnemyBehaviour->setFather(_father);
        meleeEnemyBehaviour->setScene(scene);

        if (!_data["playerSpeedPercentage"].asFloat())
            throw std::exception(
                "EnemyBehaviourPC: playerSpeedPercentage is not a float");
        meleeEnemyBehaviour->setPlayerSpeedPercentage(
            _data["playerSpeedPercentage"].asFloat());

        PlayerMovementIC* playerMovement = dynamic_cast<PlayerMovementIC*>(
            scene->getEntitybyId("Player")->getComponent("PlayerMovementIC"));

        // enemy speed depends on player speed and player speed percentage
        meleeEnemyBehaviour->setSpeed(
            playerMovement->getMovementSpeed() *
            meleeEnemyBehaviour->getPlayerSpeedPercentage());

        if (!_data["attack"].asInt())
            throw std::exception("MeleeEnemyBehaviourPC: attack is not an int");
        meleeEnemyBehaviour->setAttack(_data["attack"].asInt());

        if (!_data["attackCooldown"].asFloat())
            throw std::exception(
                "MeleeEnemyBehaviourPC: attackCooldown is not a float");
        meleeEnemyBehaviour->setAttackCooldown(
            _data["attackCooldown"].asFloat());

        return meleeEnemyBehaviour;
    };
};

REGISTER_FACTORY("MeleeEnemyBehaviourPC", MeleeEnemyBehaviourPC);
