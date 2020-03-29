#pragma once

#include "PowerUpEC.h"

class IncreaseSpeedEC : public PowerUpEC {
  private:
    double time;
    double timeEffect;
    double speedIncrement;

    double originalSpeed;

    bool startPicked;

  public:
    // probabilidad : 20%
    IncreaseSpeedEC();
    virtual ~IncreaseSpeedEC();
    virtual void destroy();

    virtual void checkEvent();

    bool timeDisappearEffect();

    void setTimeEffect(float _timeEffect);
    void setSpeedIncrement(float _speedIncrement);
    void setPickedTime(float _time);
};

/*,
    {
      "id": "Enemy",
      "components": [
        {
          "type": "TransformComponent",
          "attributes": {
            "position": [ 50, 0, 50 ],
            "orientation": [ 0, 0, 0 ],
            "scale": [ 0.1, 0, 0.1 ]
          }
        },
        {
          "type": "TridimensionalObjectRC",
          "attributes": {
            "mesh": "cube.mesh",
            "node": "nCube",
            "material": "GrassMaterial"
          }
        },
        {
          "type": "LifeC",
          "attributes": {
            "life": 150
          }
        },
        {
          "type": "RigidbodyPC",
          "attributes": {
            "position": [ 50, 0, 50 ],
            "shape": [ 5, 5, 5 ],
            "mass": 1,
            "gravity": [ 0, 0, 0 ],
            "trigger": false,
            "kinematic": true,
            "static": false,
            "friction": 500,
            "restitution": 500
          }
        },
        {
          "type": "MeleeEnemyBehaviourEC",
          "attributes": {
            "playerSpeedPercentage": 0.7,
            "attack": 10,
            "attackCooldown": 2
          }
        }
      ]
    }*/