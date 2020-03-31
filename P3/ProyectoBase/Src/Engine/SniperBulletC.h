#pragma once
#include "BulletC.h"
#include "Factory.h"

DECLARE_FACTORY(SniperBulletC);
class SniperBulletC : public BulletC {

    void dealCollision() override;
};
