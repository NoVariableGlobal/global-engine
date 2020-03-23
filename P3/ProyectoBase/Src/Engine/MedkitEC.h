#pragma once

#include "PhysicsComponent.h"

class LifeC;

class MedkitEC : public PhysicsComponent {
  private:
    int probability;
    int duration;


  public:
    MedkitEC();
    ~MedkitEC();

	void update();

	void setProbability(float _probability);
    void setDuration(float _duration);

	void onCollisionActivate();
	bool checkCollision();
};
