#pragma once

#include "Component.h"

namespace Ogre {
    typedef float Real;
    template <int dims, typename T> class Vector;
    typedef Vector<3, Real> Vector3;
} // namespace Ogre

class LifeC : public Component {
  private:
    int totalLife;
    float currentLife;
    bool invulnerability;

  public:
    LifeC();
    virtual ~LifeC();

    virtual void destroy();

    // get the current life
    float getLife();
    // set the current life
    void setLife(int _life);

    // get the total life
    int getTotalLife();
    // set the total life
    void setTotalLife(int _life);

    // subtract the damage to the life
    void doDamage(float _damage);
    // subtract the damage to the life
    void heal(float _heal);
    void setInvulnerability(bool _invulnerability);
};
