#pragma once
#include "EnemyBehaviourEC.h" 
#include <string>
class RangedEnemyBehaviourEC : public EnemyBehaviourEC {
 
private:
    std::string weaponEquipped;

 public:
    RangedEnemyBehaviourEC();
   ~RangedEnemyBehaviourEC();
    virtual void checkEvent();

	// getters and setters
    std::string getWeaponEquipped();

	void setWeaponEquipped(std::string _weaponEquipped);

	// shoot bullet in a straight line
    void shootStraight();

};
