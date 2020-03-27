#pragma once

#include "EventComponent.h"

class BulletEC : public EventComponent {
  private:
	// damage of the bullet
    float damage;

 public:
    BulletEC();
   ~BulletEC();
    virtual void destroy();
    virtual void checkEvent();

    void setDamage(float _d);
    float getDamage();
};
