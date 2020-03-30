#pragma once
#include "EnemyBehaviourEC.h"
class MeleeEnemyBehaviourEC : public EnemyBehaviourEC {

  public:
    MeleeEnemyBehaviourEC();
    ~MeleeEnemyBehaviourEC();
    virtual void checkEvent();
};
