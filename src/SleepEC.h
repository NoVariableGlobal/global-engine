#pragma once
#include "EventComponent.h"
#include "Factory.h"

#include <queue>
#include <string>
#include <vector>

// FACTORY INFRASTRUCTURE DECLARATION
DECLARE_FACTORY(SleepEC);

class Entity;

struct InfoSleep {
    std::vector<Entity*> entities_;
    float timeStart_;
    float timeEnd_;
};

class SleepEC : public EventComponent {
  private:
    std::vector<std::string> generalSleepEntities;
    std::priority_queue<InfoSleep, std::vector<InfoSleep>, std::greater<InfoSleep>> asleepEntities;

  public:
    SleepEC();
    ~SleepEC();

    virtual void checkEvent();

    // sleep the entities specified in the array of the json
    void generalSleep(float time);
    // sleep an specific entity
    void sleepAnEntity(float time, std::string id);
    // sleep all the entities with the specified tag
    void sleepTag(float time, std::string tag);

    // add a tag to the array of general sleep entities
    void setGeneralSleepEntities(std::string tag);
};
