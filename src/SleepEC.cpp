#include "SleepEC.h"
#include "ComponentsManager.h"
#include "Entity.h"
#include "FactoriesFactory.h"
#include "Factory.h"
#include "Scene.h"

#include <SDL_timer.h>
#include <json.h>

bool operator>(InfoSleep const& a, InfoSleep const& b) {
    return a.timeEnd_ > b.timeEnd_ ||
           (a.timeEnd_ == b.timeEnd_ && a.timeStart_ > b.timeStart_);
}

SleepEC::SleepEC() {}

SleepEC::~SleepEC() {}

void SleepEC::checkEvent() {
    if (!asleepEntities.empty()) {
        float actualTime = SDL_GetTicks();

        InfoSleep top = asleepEntities.top();
        while (top.timeEnd_ <= actualTime) {
            for (Entity* entity : top.entities_) {
                entity->setAsleep(false);
            }

            asleepEntities.pop();
            if (asleepEntities.empty())
                break;

            top = asleepEntities.top();
        }
    }
}

void SleepEC::generalSleep(float time) {
    std::vector<Entity*> entitiesToPause;
    for (std::string tag : generalSleepEntities) {

        std::vector<Entity*> tmp = scene->getEntitiesbyTag(tag);
        for (Entity* entity : tmp) {
            entity->setAsleep(true);
            entitiesToPause.push_back(entity);
        }
    }

    float startTime = SDL_GetTicks();
    asleepEntities.push({entitiesToPause, startTime, time * 1000 + startTime});
}

void SleepEC::sleepAnEntity(float time, std::string id) {
    Entity* entity = scene->getEntitybyId(id);
    entity->setAsleep(true);

    std::vector<Entity*> entitiesToPause;
    entitiesToPause.push_back(entity);

    float startTime = SDL_GetTicks();
    asleepEntities.push({entitiesToPause, startTime, time * 1000 + startTime});
}

void SleepEC::sleepTag(float time, std::string tag) {
    std::vector<Entity*> entitiesToPause = scene->getEntitiesbyTag(tag);
    for (Entity* entity : entitiesToPause) {
        entity->setAsleep(true);
    }

    float startTime = SDL_GetTicks();
    asleepEntities.push({entitiesToPause, startTime, time * 1000 + startTime});
}

void SleepEC::setGeneralSleepEntities(std::string tag) {
    generalSleepEntities.push_back(tag);
}

// FACTORY INFRASTRUCTURE DEFINITION

SleepECFactory::SleepECFactory() = default;

Component* SleepECFactory::create(Entity* _father, Json::Value& _data,
                                  Scene* _scene) {
    SleepEC* sleep = new SleepEC();
    _scene->getComponentsManager()->addEC(sleep);

    sleep->setFather(_father);
    sleep->setScene(_scene);

    if (_data["generalSleepTags"].isArray()) {
        if (!_data["generalSleepTags"][0].isString())
            throw std::exception("SleepC: generalSleepTags is not an array of "
                                 "strings. Write the tags of the entities.");

        std::vector<std::string> tags;

        int size = _data["generalSleepTags"].size();
        for (int i = 0; i < size; i++)
            sleep->setGeneralSleepEntities(
                _data["generalSleepTags"][i].asString());
    }

    return sleep;
}

DEFINE_FACTORY(SleepEC);
