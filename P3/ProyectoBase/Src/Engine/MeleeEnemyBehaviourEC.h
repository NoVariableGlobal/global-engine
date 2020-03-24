#pragma once
#include "EnemyBehaviourEC.h"
class MeleeEnemyBehaviourEC : public EnemyBehaviourEC {
 
 public:
    MeleeEnemyBehaviourEC();
   ~MeleeEnemyBehaviourEC();
   virtual void destroyMyself();
    virtual void checkEvent();
};
