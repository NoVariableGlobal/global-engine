#pragma once

#include "EventComponent.h"

class DestroyAfterSecsEC : public EventComponent {
  private:
    int lifeTime = 0;
    bool firstTime = true;
    float creationTime = 0;

  public:
    DestroyAfterSecsEC() = default;
    ~DestroyAfterSecsEC() = default;

    virtual void checkEvent();

    void setLifeTime(int n);
};