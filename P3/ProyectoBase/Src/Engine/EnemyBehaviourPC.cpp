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

EnemyBehaviourPC::EnemyBehaviourPC(): speed(0.0f), playerSpeedPercentage(0.0f), attack(0) {}

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

bool EnemyBehaviourPC::getCollisionWithPlayer() { return collisionWithPlayer; }

void EnemyBehaviourPC::setCollisionWithPlayer(bool _collisionWithPlayer) {
    collisionWithPlayer = _collisionWithPlayer;
}

float EnemyBehaviourPC::getSpeed() { return speed; }

float EnemyBehaviourPC::getPlayerSpeedPercentage() {
    return playerSpeedPercentage;
}

int EnemyBehaviourPC::getAttack() { return attack; }

void EnemyBehaviourPC::setSpeed(float _speed) { speed = _speed; }

void EnemyBehaviourPC::setPlayerSpeedPercentage(
    float _playerSpeedPercentage) {
    playerSpeedPercentage = _playerSpeedPercentage;
}

void EnemyBehaviourPC::setAttack(float _attack) { attack = _attack; }

