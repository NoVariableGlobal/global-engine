#pragma once

#include "Component.h"

class BulletC : public Component {
  private:
	// damage of the bullet
    float damage;

 public:
    BulletC();
   ~BulletC();
    virtual void destroy();

    void setDamage(float _d);
    float getDamage();

    // method that specify what the bullet will do if it collide with something
    // in the case of a normal bullet, it will be destroyed
    virtual void dealCollision();
};
