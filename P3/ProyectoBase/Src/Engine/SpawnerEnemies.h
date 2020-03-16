#pragma once
#include "Spawner.h"
class TransformComponent;

class SpawnerEnemies :
  public Spawner
{
private: 
  TransformComponent* transform = nullptr;
public:
  virtual void checkEvent() override;

};

