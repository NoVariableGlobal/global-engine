#pragma once
#include "EnemyBehaviourEC.h" 
class RangedEnemyBehaviourEC : public EnemyBehaviourEC {
 
 public:
    RangedEnemyBehaviourEC();
   ~RangedEnemyBehaviourEC();
    virtual void checkEvent();
};
