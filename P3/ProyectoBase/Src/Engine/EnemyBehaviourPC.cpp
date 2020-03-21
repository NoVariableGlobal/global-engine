#include "EnemyBehaviourPC.h"
#include "ComponentsManager.h"
#include "FactoriesFactory.h"
#include "Factory.h"
#include "Scene.h"
#include <Entity.h>
#include <json.h>
#include "TransformComponent.h"
#include "OgreRoot.h"
#include "RigidbodyPC.h"

EnemyBehaviourPC::EnemyBehaviourPC() {}

EnemyBehaviourPC::~EnemyBehaviourPC() {}

void EnemyBehaviourPC::update() {
    TransformComponent* transform = dynamic_cast<TransformComponent*>(
        father->getComponent("TransformComponent"));

    // TO DO: obtain player position
    Ogre::Vector3* playerPosition = nullptr;

    Ogre::Vector3 directionToPlayer =
        Ogre::Vector3(playerPosition->x - transform->getPosition().x,
                      playerPosition->y - transform->getPosition().y,
                      playerPosition->z - transform->getPosition().z)
            .normalisedCopy();

	// TO DO: check collision with player
	//collisionWithPlayer = checkCollision(player);

	// if not colliding with player enemy moves towards player
    if (!collisionWithPlayer) {
        transform->setPosition(Ogre::Vector3(
            transform->getPosition().x + directionToPlayer.x * speed,
            transform->getPosition().y,
            transform->getPosition().z + directionToPlayer.z * speed));
	}

	// set orientation towards player
    transform->setOrientation(directionToPlayer);
}

float EnemyBehaviourPC::getSpeed() { return speed; }

float EnemyBehaviourPC::getPlayerSpeedPercentage() {
    return playerSpeedPercentage;
}

void EnemyBehaviourPC::setSpeed(float _speed) { speed = _speed; }

void EnemyBehaviourPC::setPlayerSpeedPercentage(
    float _playerSpeedPercentage) {
    playerSpeedPercentage = _playerSpeedPercentage;
}

// FACTORY INFRASTRUCTURE
class EnemyBehaviourPCFactory final : public ComponentFactory {
  public:
    EnemyBehaviourPCFactory() = default;

    Component* create(Entity* _father, Json::Value& _data,
                      Scene* scene) override {
        EnemyBehaviourPC* enemyBehaviour = new EnemyBehaviourPC();
        scene->getComponentsManager()->addPC(enemyBehaviour);

        enemyBehaviour->setFather(_father);
        enemyBehaviour->setScene(scene);

        if (!_data["playerSpeedPercentage"].asFloat())
            throw std::exception(
                "EnemyBehaviourPC: playerSpeedPercentage is not a float");
        enemyBehaviour->setPlayerSpeedPercentage(
            _data["playerSpeedPercentage"].asFloat());

		// TO DO: obtain player speed
        // enemyBehaviour->setSpeed(playerSpeed *
        // enemyBehaviour->getPlayerSpeedPercentage());

        return enemyBehaviour;
    };
};

REGISTER_FACTORY("EnemyBehaviourPC", EnemyBehaviourPC);
