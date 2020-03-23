#pragma once

#include "Component.h"

class PowerUpEC : public Component {
  private:
    double
        timeBeforeDelete; // time before the power up is deleted if not picked
    double timeOfEffect; // time during which the effect of the power up will be
                         // applied
    // bool startEffect; // indicates that the power up has been picked

	// In json files they are called respectively time and timeEffect

    bool picked; // determines if the power up has been picked before being
                 // deleted

  public:
    /*
     * updates the time on the power up before deleting it if not picked by the
     * player yet
     */
    virtual void update();
    /*
     * method defined by its children
     */
    virtual void onPickUp() = 0;

    // counts the time before deleting the power up if not picked by the player
    // before
    bool timeToDisappear();

    // setters
    void setTimeBeforeDelete(float _timeBeforeDelete);
    void setTimeOfEffect(float _timeOfEffect);
    void setPicked(bool _picked);

    // getters
    bool isPicked();
};
