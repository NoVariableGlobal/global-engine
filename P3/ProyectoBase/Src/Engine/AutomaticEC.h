#pragma once
#include "EventComponent.h"
#include "Factory.h"

DECLARE_FACTORY(AutomaticEC);
// class to detect when to fire an automatic weapon depending on its cadence
class AutomaticEC : public EventComponent {
  private:
    double cadence;
    double lastTimecadence = 0;
    bool shoot = false;

  public:
    AutomaticEC();
    ~AutomaticEC();
    virtual void checkEvent() override;
    bool timeCadence();
    void setCadence(double _cadence);
    void setShoot(bool _shoot);
};