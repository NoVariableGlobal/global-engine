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
#include <iostream>

EnemyBehaviourPC::EnemyBehaviourPC(): speed(0.0f), playerSpeedPercentage(0.0f), attack(0), attackCooldown(0.0f) {}

EnemyBehaviourPC::~EnemyBehaviourPC() {}

void EnemyBehaviourPC::checkEvent() {
    TransformComponent* transform = dynamic_cast<TransformComponent*>(
        father->getComponent("TransformComponent"));
    RigidbodyPC* rb =
        dynamic_cast<RigidbodyPC*>(
        father->getComponent("RigidbodyPC"));

    // obtain player position
    TransformComponent* playerTransform = dynamic_cast<TransformComponent*>(
        scene->getEntitybyId("Player")->getComponent("TransformComponent"));
    Ogre::Vector3 playerPosition = playerTransform->getPosition();

    Ogre::Vector3 directionToPlayer =
        Ogre::Vector3(playerPosition.x - transform->getPosition().x,
                      playerPosition.y - transform->getPosition().y,
                      playerPosition.z - transform->getPosition().z)
            .normalisedCopy();

	// check collision with player
    collisionWithPlayer = rb->collidesWith("Player");

	// if not colliding with player enemy moves towards player
    if (!collisionWithPlayer) {
        Ogre::Vector3 force = Ogre::Vector3(directionToPlayer.x * speed, 0.0f, directionToPlayer.z * speed);
        rb->addForce(force, Ogre::Vector3(0.0f,0.0f,0.0f));	
	}

	// set orientation towards player
    transform->setOrientation(directionToPlayer);
}

bool EnemyBehaviourPC::timeToAttack() {
    float seconds = clock() / static_cast<float>(CLOCKS_PER_SEC);

    if (seconds - lastTimeAttacked >= attackCooldown) {
        lastTimeAttacked = seconds;
        return true;
    }

    return false;
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

float EnemyBehaviourPC::getAttackCooldown() { return attackCooldown; }

float EnemyBehaviourPC::getLastTimeAttacked() { return lastTimeAttacked; }

void EnemyBehaviourPC::setSpeed(float _speed) { speed = _speed; }

void EnemyBehaviourPC::setPlayerSpeedPercentage(
    float _playerSpeedPercentage) {
    playerSpeedPercentage = _playerSpeedPercentage;
}

void EnemyBehaviourPC::setAttack(float _attack) { attack = _attack; }

void EnemyBehaviourPC::setAttackCooldown(float _attackCooldown) {
    attackCooldown = _attackCooldown;
}

void EnemyBehaviourPC::setLastTimeAttacked(float _lastTimeAttacked) {
    lastTimeAttacked = _lastTimeAttacked;
}

