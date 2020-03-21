#include "GunC.h"
#include "Scene.h"

GunC::GunC() {}

GunC::~GunC() {}

bool GunC::reload() {
    if (_bulletchamber < _bulletchamberMax && _munition > 0) {
        int gunreload = _bulletchamberMax - _bulletchamber;

        if (gunreload > _munition)
            gunreload = _munition;

        _bulletchamber += gunreload;
        _munition -= gunreload;

        return true;
    } else
        return false;
}

bool GunC::shoot() {
    if (_bulletchamber > 0) 
    {
        _bulletchamber--;
       // scene->getEntitybyId("pool").createBullet(myBulletType);
        return true;
    } else
        return false;
}

int GunC::getbulletchamber() { return _bulletchamber; }

int GunC::getmunition() { return _munition; }

float GunC::getcadence() { return _cadence; }

float GunC::getdamage() { return _damage; }

bool GunC::getsemiautomatic() { return _semiautomatic; }

void GunC::setbulletchamber(int bulletchamberMax) {
    _bulletchamberMax = bulletchamberMax;
}

void GunC::setmunition(int munition) { _munition = munition; }

void GunC::setcadence(float cadence) { _cadence = cadence; }

void GunC::setdamage(float damage) { _damage = damage; }

void GunC::setsemiautomatic(bool semiautomatic) {
    _semiautomatic = semiautomatic;
}



bool GunC::mmunitionleft() {
    if (_bulletchamber == 0 && _munition == 0)
        return false;
    else
        return true;
}
