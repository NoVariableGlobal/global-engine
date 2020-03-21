#include "MeleeEnemyBehaviourPC.h"
#include "ComponentsManager.h"
#include "EnemyBehaviourPC.h"
#include "FactoriesFactory.h"
#include "Factory.h"
#include "OgreRoot.h"
#include "Scene.h"
#include <Entity.h>
#include <json.h>

MeleeEnemyBehaviourPC::MeleeEnemyBehaviourPC(): EnemyBehaviourPC() {}

MeleeEnemyBehaviourPC::~MeleeEnemyBehaviourPC() {}

void MeleeEnemyBehaviourPC::update() {
    EnemyBehaviourPC::update();

    if (getCollisionWithPlayer()) {
		// TO DO: attack player
		// player->takeDamage(attack);
	}
}

// FACTORY INFRASTRUCTURE
class MeleeEnemyBehaviourPCFactory final : public ComponentFactory {
  public:
    MeleeEnemyBehaviourPCFactory() = default;

    Component* create(Entity* _father, Json::Value& _data,
                      Scene* scene) override {
        MeleeEnemyBehaviourPC* meleeEnemyBehaviour = new MeleeEnemyBehaviourPC();
        scene->getComponentsManager()->addPC(meleeEnemyBehaviour);

        meleeEnemyBehaviour->setFather(_father);
        meleeEnemyBehaviour->setScene(scene);

        if (!_data["playerSpeedPercentage"].asFloat())
            throw std::exception(
                "EnemyBehaviourPC: playerSpeedPercentage is not a float");
        meleeEnemyBehaviour->setPlayerSpeedPercentage(
            _data["playerSpeedPercentage"].asFloat());

        // TO DO: obtain player speed
        // meleeEnemyBehaviour->setSpeed(playerSpeed *
        // meleeEnemyBehaviour->getPlayerSpeedPercentage());

		if (!_data["attack"].asInt())
            throw std::exception(
                "MeleeEnemyBehaviourPC: attack is not an int");
        meleeEnemyBehaviour->setAttack(
            _data["attack"].asInt());

        return meleeEnemyBehaviour;
    };
};

REGISTER_FACTORY("MeleeEnemyBehaviourPC", MeleeEnemyBehaviourPC);
