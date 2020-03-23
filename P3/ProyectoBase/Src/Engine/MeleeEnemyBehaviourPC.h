#pragma once
#include "EnemyBehaviourPC.h"
class MeleeEnemyBehaviourPC : public EnemyBehaviourPC {
 
 public:
    MeleeEnemyBehaviourPC();
   ~MeleeEnemyBehaviourPC();
    virtual void checkEvent();
};
