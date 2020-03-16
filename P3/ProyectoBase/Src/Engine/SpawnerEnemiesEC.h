#pragma once
#include "Spawner.h"
class TransformComponent;

class SpawnerEnemiesEC : public Spawner
{
private: 
  TransformComponent* transform = nullptr;
public:
  virtual void checkEvent() override;

  void setTransform(TransformComponent* trans);
};

