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
 public:
    EnemyBehaviourPC();
   ~EnemyBehaviourPC();
    virtual void update();

	// getters and setters
	float getSpeed();
    float getPlayerSpeedPercentage();

	void setSpeed(float _speed);
    void setPlayerSpeedPercentage(float _playerSpeedPercentage);








};
