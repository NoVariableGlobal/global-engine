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

    void setPicked(bool picked);
    void setTime(float time);
    void setDuration(float duration);
    void resetTime();

    float getTime();
    bool getPicked();
    bool getCollisionWithPlayer();
    bool timeDisappearEffect();
};
