#pragma once
#include "GunC.h" 
#include "Factory.h"

DECLARE_FACTORY(SniperGunC);
class SniperGunC : public GunC {

  
    virtual void destroy();

    virtual bool shoot();

};
