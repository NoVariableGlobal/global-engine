#pragma once
#include "EnemyBehaviourEC.h"
#include <string>
class RangedEnemyBehaviourEC : public EnemyBehaviourEC {

  private:
    std::string weaponEquipped;
    int arcPellets;
    int arcAngleDistance;
    int bulletSpeed;

  public:
    RangedEnemyBehaviourEC();
    ~RangedEnemyBehaviourEC();
    virtual void checkEvent();

    // getters and setters
    std::string getWeaponEquipped();
    int getArcPellets();
    int getArcAngleDistance();
    int getBulletSpeed();

    void setWeaponEquipped(std::string _weaponEquipped);
    void setArcPellets(int _arcPellets);
    void setArcAngleDistance(int _arcAngleDistance);
    void setBulletSpeed(int _bulletSpeed);

    // shoot bullets in different ways depending on weapon equipped, arcPellets,
    // arcAngleDistance and bulletSpeed
    void shoot();
};
