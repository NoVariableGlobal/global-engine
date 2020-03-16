#pragma once
#include "Spawner.h"
#include "OgreVector4.h"

class SpawnerFloorRandomEC : public Spawner
{
private:
  Ogre::Vector4f floorDimensions = Ogre::Vector4f();
  bool first = true;
public:
  virtual void checkEvent() override;
};

