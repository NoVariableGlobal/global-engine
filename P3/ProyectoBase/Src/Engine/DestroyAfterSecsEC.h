#pragma once

#include "EventComponent.h"

class DestroyAfterSecsEC : public EventComponent {
  private:
    int lifeTime;
    bool firstTime = true;
    float creationTime = 0;

  public:
    DestroyAfterSecsEC() = default;
    ~DestroyAfterSecsEC() = default;

    virtual void destroyMyself();

    virtual void checkEvent();

	void setLifeTime(int n);
};