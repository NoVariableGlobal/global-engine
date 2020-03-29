#include "MeleeEnemyBehaviourEC.h"
#include "ComponentsManager.h"
#include "EnemyBehaviourEC.h"
#include "Entity.h"
#include "FactoriesFactory.h"
#include "Factory.h"
#include "LifeC.h"
#include "OgreRoot.h"
#include "PlayerMovementIC.h"
#include "RigidbodyPC.h"
#include "Scene.h"
#include <json.h>

#include <iostream>
MeleeEnemyBehaviourEC::MeleeEnemyBehaviourEC() : EnemyBehaviourEC() {}

MeleeEnemyBehaviourEC::~MeleeEnemyBehaviourEC() {}

void MeleeEnemyBehaviourEC::destroy() {
    setActive(false);
    scene->getComponentsManager()->eraseEC(this);
}

void MeleeEnemyBehaviourEC::checkEvent() {
    EnemyBehaviourEC::checkEvent();

    // attack every attackCooldown seconds
    if (timeToAttack()) {
        if (active) {
            // if enemy is colliding with player
            if (getCollisionWithPlayer()) {
                // attack player
                LifeC* playerHealth = dynamic_cast<LifeC*>(
                    scene->getEntitybyId("Player")->getComponent("LifeC"));
                playerHealth->doDamage(getAttack());
            }
        }

    }
}

// FACTORY INFRASTRUCTURE
class MeleeEnemyBehaviourECFactory final : public ComponentFactory {
  public:
    MeleeEnemyBehaviourECFactory() = default;

    Component* create(Entity* _father, Json::Value& _data,
                      Scene* scene) override {
        MeleeEnemyBehaviourEC* meleeEnemyBehaviour =
            new MeleeEnemyBehaviourEC();
        scene->getComponentsManager()->addEC(meleeEnemyBehaviour);

        meleeEnemyBehaviour->setFather(_father);
        meleeEnemyBehaviour->setScene(scene);

        if (!_data["speed"].isDouble())
            throw std::exception("MeleeEnemyBehaviourEC: speed is not a float");
        meleeEnemyBehaviour->setSpeed(_data["speed"].asFloat());

        if (!_data["attack"].isInt())
            throw std::exception("MeleeEnemyBehaviourEC: attack is not an int");
        meleeEnemyBehaviour->setAttack(_data["attack"].asInt());

        if (!_data["attackCooldown"].isDouble())
            throw std::exception(
                "MeleeEnemyBehaviourEC: attackCooldown is not a float");
        meleeEnemyBehaviour->setAttackCooldown(
            _data["attackCooldown"].asFloat());

        return meleeEnemyBehaviour;
    };
};

REGISTER_FACTORY("MeleeEnemyBehaviourEC", MeleeEnemyBehaviourEC);
