#pragma once
#include "SpawnerEC.h"
class TransformComponent;

class SpawnerEnemiesEC : public SpawnerEC {
  private:
    TransformComponent* transform = nullptr;

  public:
    virtual void destroy();
    virtual void checkEvent() override;

    void setTransform(TransformComponent* trans);
};
