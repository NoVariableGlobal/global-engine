#pragma once

#include "Component.h"

#include <map>
#include <string>

class PowerUpTrackerC : public Component {
  private:
    std::map<std::string, Component*> powerUps;

  public:
    PowerUpTrackerC() = default;
    ~PowerUpTrackerC() = default;

    void destroy();

    Component* getComponent(std::string name);
    void addPowerUp(std::string name, Component* powerUp);
    void removePowerUp(std::string name);
};
