#pragma once
#include "EventComponent.h"

class SemiAutomaticEC : public EventComponent {
  private:
    double cadence;
    float lastTimecadence = 0;
    bool shoot = false;
  public:
    SemiAutomaticEC();
    ~SemiAutomaticEC();
    virtual void destroy();
    virtual void checkEvent() override;
    bool timeCadence();
    void setCadence(double _cadence);
    void setShoot(bool _shoot);
};