#pragma once

#include "EventComponent.h"

class PowerUpEC : public EventComponent {
  private:
    float durationTotal_ = 0.0f;
    float time_ = 0.0f;
    bool collisionWithPlayer_ = false;
    bool start_ = false;
    bool picked_ = false;

  protected:
    virtual void onDestroy();

  public:
    PowerUpEC();
    ~PowerUpEC();
    virtual void checkEvent();

    void setPicked(bool picked) { picked_ = picked; }
    void setTime(float time) { time_ = time; }
    void setDuration(float duration);

    bool getPicked() { return picked_; }
    float getTime() { return time_; }
    bool getCollisionWithPlayer();
    bool timeDisappearEffect();

    // Destroys the PhysicsComponent, setting itself as inactive and
    // removing itself from the scene.
    virtual void destroy();
};
