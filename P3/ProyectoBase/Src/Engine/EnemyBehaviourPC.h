#pragma once
#include "PhysicsComponent.h"
class EnemyBehaviourPC : public PhysicsComponent {
  private:
	// speed at which enemy follows the player
    float speed;
	// enemy speed is (player speed * player speed percentage)
    float playerSpeedPercentage;

	// true if enemy is colliding with player
	bool collisionWithPlayer = false;

	// amount of damage the enemy deals to the player
	int attack;

	// enemy deals damage every "attackCooldown" seconds
    float attackCooldown;
    int attackFrames;

 public:
    EnemyBehaviourPC();
   ~EnemyBehaviourPC();
    virtual void update();

	// getters and setters
	float getSpeed();
    float getPlayerSpeedPercentage();
    bool getCollisionWithPlayer();
    int getAttack();
    float getAttackCooldown();
    int getAttackFrames();

	void setSpeed(float _speed);
    void setPlayerSpeedPercentage(float _playerSpeedPercentage);
    void setCollisionWithPlayer(bool _collisionWithPlayer);
    void setAttack(float _attack);
    void setAttackCooldown(float _attackCooldown);
    void setAttackFrames(int _attackFrames);
};
