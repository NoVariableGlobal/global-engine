#pragma once
#include "SpawnerEC.h" 
#include "Factory.h"

// FACTORY INFRASTRUCTURE DECLARATION
DECLARE_FACTORY(SpawnerEnemiesEC);
class TransformComponent;

class SpawnerEnemiesEC : public SpawnerEC {
  private:
    TransformComponent* transform = nullptr;

  public:
    virtual void checkEvent() override;

    void setTransform(TransformComponent* trans);
};
