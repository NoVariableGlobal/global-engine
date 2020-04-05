#include "SoundComponent.h"
#include "SoundContext.h"
#include "FactoriesFactory.h"
#include "Entity.h"
#include "json.h"
#include "Scene.h"
#include "ComponentsManager.h"

SoundComponent::SoundComponent() : Component(){
    channels_ = std::map<std::string, Channel*>();
}

SoundComponent::~SoundComponent() = default;

void SoundComponent::playSound(const std::string& id) {
    channels_[id] = SoundContext::getInstance()->playSound(
        SoundContext::getInstance()->getSound(id));
}

void SoundComponent::stopSound(const std::string& id) {
    SoundContext::getInstance()->stopSound(&channels_[id]);
}

void SoundComponent::destroy() {}

void SoundComponent::addSoundToList(const std::string& id) {
    channels_[id] = nullptr;
}


// FACTORY INFRASTRUCTURE DEFINITION

SoundComponentFactory::SoundComponentFactory() = default;

Component* SoundComponentFactory::create(Entity* _father,
                                             Json::Value& _data,
                                             Scene* _scene) {
    SoundComponent* soundComponent = new SoundComponent();

    soundComponent->setFather(_father);
    soundComponent->setScene(_scene);

    if (!_data["sounds"].isArray())
        throw std::exception("SoundComponent: sounds is not an array");
    
    auto sounds = _data["sounds"];
    int soundsSize = sounds.size();
    for (int i = 0; i < soundsSize; ++i) {
        if (!sounds[i].isString()) {
          std::string str = "SoundComponent: sounds[" + std::to_string(i) +
                              "] is not an array";
            throw std::exception(str.c_str());
        }
        soundComponent->addSoundToList(sounds[i].asString());
    }

    return soundComponent;
}

DEFINE_FACTORY(SoundComponent);