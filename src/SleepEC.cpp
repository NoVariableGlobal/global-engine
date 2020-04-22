#include "SleepEC.h"
#include "ComponentsManager.h"
#include "Entity.h"
#include "FactoriesFactory.h"
#include "Factory.h"
#include "Scene.h"

#include <SDL_timer.h>
#include <json.h>

bool operator>(InfoSleep const& a, InfoSleep const& b) {
    return a.timeEnd > b.timeEnd ||
           (a.timeEnd == b.timeEnd && a.timeStart > b.timeStart);
}

void SleepEC::checkEvent() {
    if (!asleepEntities_.empty()) {
        const int actualTime = SDL_GetTicks();

        InfoSleep top = asleepEntities_.top();
        while (static_cast<int>(top.timeEnd) <= actualTime) {
            for (Entity* entity : top.entities) {
                entity->setAsleep(false);
            }

            asleepEntities_.pop();
            if (asleepEntities_.empty())
                break;

            top = asleepEntities_.top();
        }
    }
}

void SleepEC::generalSleep(const float time) {
    std::vector<Entity*> entitiesToPause = {};
    for (const auto tag : generalSleepEntities_) {

        std::vector<Entity*> tmp = scene_->getEntitiesByTag(tag);
        for (Entity* entity : tmp) {
            entity->setAsleep(true);
            entitiesToPause.push_back(entity);
        }
    }

    const auto startTime = static_cast<float>(SDL_GetTicks());
    asleepEntities_.push({entitiesToPause, startTime, time * 1000 + startTime});
}

void SleepEC::sleepAnEntity(const float time, const std::string& id) {
    Entity* entity = scene_->getEntityById(id);
    entity->setAsleep(true);

    const std::vector<Entity*> entitiesToPause = {entity};
    const auto startTime = static_cast<float>(SDL_GetTicks());
    asleepEntities_.push({entitiesToPause, startTime, time * 1000 + startTime});
}

void SleepEC::sleepTag(const float time, const std::string& tag) {
    std::vector<Entity*> entitiesToPause = scene_->getEntitiesByTag(tag);
    for (Entity* entity : entitiesToPause) {
        entity->setAsleep(true);
    }

    const auto startTime = static_cast<float>(SDL_GetTicks());
    asleepEntities_.push({entitiesToPause, startTime, time * 1000 + startTime});
}

void SleepEC::setGeneralSleepEntities(const std::string& tag) {
    generalSleepEntities_.push_back(tag);
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

        const int size = _data["generalSleepTags"].size();
        for (int i = 0; i < size; i++)
            sleep->setGeneralSleepEntities(
                _data["generalSleepTags"][i].asString());
    }

    return sleep;
}

DEFINE_FACTORY(SleepEC);
