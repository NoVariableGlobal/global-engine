#pragma once
#include "EventComponent.h"

// class to detect when to fire an automatic weapon depending on its cadence
class SemiAutomaticEC : public EventComponent {
  private:
    double cadence;
    double lastTimecadence = 0;
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