#pragma once

#include "EventComponent.h"
#include <string>
#include <vector>

class TransformComponent;

class PowerUpC : public EventComponent {
  private:
    TransformComponent* transform;

    float probability;
    float duration;

    bool instantaneous;

    int type;

  public:
    void checkEvent();

	void update();

	bool isCollisionWithPlayer();

    void setProbability(float _probability);
    void setDuration(float _duration);
    void setType(int _type);
    void isInstantaneous(bool _instantaneous);
};
