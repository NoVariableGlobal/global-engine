#include "GunC.h"

GunC::GunC(int _bulletchamber, int _munition, int _cadence, int _damage,
           bool _semiautomatic)
    : bulletchamber(_bulletchamber), bulletchamberMax(_bulletchamber),
      munition(_munition), cadence(_cadence), damage(_damage),
      semiautomatic(_semiautomatic) {}

GunC::~GunC() {}

bool GunC::reload() {
    if (bulletchamber != bulletchamberMax && munition > 0) {
        int gunreload = bulletchamberMax - bulletchamber;
        if (gunreload > munition)
            gunreload = munition;
        bulletchamber += gunreload;
        munition -= gunreload;
        return true;
    } else
        return false;
}

bool GunC::shoot() {
    if (bulletchamber > 0) {
        bulletchamber--;
        return true;
    } else
        return false;
}

int GunC::getbulletchamber() { return bulletchamber; }

int GunC::getmunition() { return munition; }

int GunC::getcadence() { return cadence; }

int GunC::getdamage() { return damage; }

bool GunC::getsemiautomatic() { return semiautomatic; }

bool GunC::mmunitionleft() {
    if (bulletchamber == 0 && munition == 0)
        return false;
    else
        return true;
}
