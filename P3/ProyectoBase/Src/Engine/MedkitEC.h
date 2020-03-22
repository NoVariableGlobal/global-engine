#pragma once

#include "PowerUpC.h"
#include "TransformComponent.h"

class LifeC;

class MedkitEC : public PowerUpC {
  private:
    int chance;

	TransformComponent* medkitEC;

  public:
    MedkitEC();
    ~MedkitEC();

	void onCollisionActivate();
	bool checkCollision();
};
