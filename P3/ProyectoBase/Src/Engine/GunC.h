#pragma once
#include "Component.h"
#include <string>
class TransformComponent;

class GunC : public Component {
  protected:
    int _bulletchamber;    // Ammunition in chamber
    int _bulletchamberMax; // Total ammunition in chamber
    int _munition;         // Total ammunition stored
    float _cadence;        // Gun cadence
    float _damage;         // Gun damage by bullet
    bool _semiautomatic;   // One shot or multiple shot gun
    bool infiniteAmmo_;    // Whether or not this gun has infinite ammo
    std::string _myBulletType;
    TransformComponent* myTransform;

  public:
    GunC();
    ~GunC();

    // Tries to reload the gun, returns false if failed
    bool reload();

    // Tries to fire a shot, returns false if gun is empty
    virtual bool shoot() = 0;

    // Returns wheter or not there is ammunition left in the gun
    bool mmunitionleft();

    // Getters
    int getbulletchamber();  // Return the remaining ammunition in the chamber
    int getmunition();       // Return the remaining ammo
    float getcadence();      // Returns the cadence of a bullet
    float getdamage();       // Returns damage from a bullet
    bool getsemiautomatic(); // Returns if a weapon is semi-automatic
    bool getInfiniteAmmo();  // Returns if the weapon's ammo is infinite
    // Setters
    void setbulletchamber(int bulletchamberMax);
    void setmunition(int munition);
    void setcadence(float cadence);
    void setdamage(float damage);
    void setsemiautomatic(bool semiautomatic);
    void setInfiniteAmmo(bool infinite);

    void setTransform(TransformComponent* trans);
};