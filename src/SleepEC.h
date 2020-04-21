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
    std::vector<Entity*> entities;
    float timeStart;
    float timeEnd;
};

class SleepEC final : public EventComponent {
    std::vector<std::string> generalSleepEntities_;
    std::priority_queue<InfoSleep, std::vector<InfoSleep>, std::greater<>>
        asleepEntities_;

  public:
    void checkEvent() override;

    // sleep the entities specified in the array of the json
    void generalSleep(float time);
    // sleep an specific entity
    void sleepAnEntity(float time, const std::string& id);
    // sleep all the entities with the specified tag
    void sleepTag(float time, const std::string& tag);

    // add a tag to the array of general sleep entities
    void setGeneralSleepEntities(const std::string& tag);
};
