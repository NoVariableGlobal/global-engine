#pragma once
#include "EnemyBehaviourEC.h" 
#include "Factory.h"

// FACTORY INFRASTRUCTURE DECLARATION
DECLARE_FACTORY(MeleeEnemyBehaviourEC);
class MeleeEnemyBehaviourEC : public EnemyBehaviourEC {

  public:
    MeleeEnemyBehaviourEC();
    ~MeleeEnemyBehaviourEC();
    virtual void checkEvent();
};
