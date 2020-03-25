#pragma once
#include "OgreVector4.h"
#include "SpawnerEC.h"

class SpawnerFloorRandomEC : public SpawnerEC {
  private:
    Ogre::Vector4f floorDimensions = Ogre::Vector4f();
    bool first = true;

  public:
    virtual void destroy();
    virtual void checkEvent() override;
};
