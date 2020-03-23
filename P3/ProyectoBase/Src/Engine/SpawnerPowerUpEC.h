#pragma once
#include "SpawnerFloorRandomEC.h"

class TransformComponent;

class SpawnerPowerUpEC : public SpawnerFloorRandomEC {
  private:
    TransformComponent* transform = nullptr;

    double duration;
    bool instantaneous;

  public:
    virtual void checkEvent() override;

	void setDuration(double _duration);
    void setInstantaneous(bool _isInstant);
};
