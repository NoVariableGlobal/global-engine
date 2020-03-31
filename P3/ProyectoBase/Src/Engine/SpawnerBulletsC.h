#pragma once

#include "Component.h"

#include <string>
#include "Factory.h"

// FACTORY INFRASTRUCTURE DECLARATION
DECLARE_FACTORY(SpawnerBulletsC);

class Entity;

class SpawnerBulletsC : public Component {
  private:
    int count = 0;

  public:
    SpawnerBulletsC();
    virtual ~SpawnerBulletsC();

    virtual void destroy();

    Entity* getBullet(std::string _type);
};
