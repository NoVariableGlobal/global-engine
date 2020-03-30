#pragma once

#include "EventComponent.h"

class PowerUpEC : public EventComponent {
  private:
    float durationTotal;
    float time;
    float timeStart;
    bool collisionWithPlayer;
    bool start;

  protected:
    bool picked;

  public:
    PowerUpEC();
    ~PowerUpEC();
    virtual void checkEvent();

    void setDuration(float _duration);
    bool getCollisionWithPlayer();
    bool timeDisappear();

    // Destroys the PhysicsComponent, setting itself as inactive and
    // removing itself from the scene.
    virtual void destroy();
};
