#include "SoundComponent.h"
#include "ComponentsManager.h"
#include "Entity.h"
#include "FactoriesFactory.h"
#include "Scene.h"
#include "SoundContext.h"
#include "json.h"

SoundComponent::SoundComponent() : Component() {
    channels_ = std::map<std::string, Channel*>();
}

SoundComponent::~SoundComponent() {
    for (auto it = channels_.begin(); it != channels_.end(); ++it)
        delete it->second;
}

void SoundComponent::playSound(const std::string& id) {

    if (channels_[id] != nullptr)
        delete channels_[id];

    channels_[id] = SoundContext::getInstance()->playSound(id);
}

void SoundComponent::stopSound(const std::string& id) {
    if (channels_[id] != nullptr)
        SoundContext::getInstance()->stopSound(&channels_[id]);
}

void SoundComponent::destroy() {}

void SoundComponent::addSoundToList(const std::string& id) {
    channels_[id] = nullptr;
}

// FACTORY INFRASTRUCTURE DEFINITION

SoundComponentFactory::SoundComponentFactory() = default;

Component* SoundComponentFactory::create(Entity* _father, Json::Value& _data,
                                         Scene* _scene) {
    SoundComponent* soundComponent = new SoundComponent();

    soundComponent->setFather(_father);
    soundComponent->setScene(_scene);

    _scene->getComponentsManager()->addDC(soundComponent);

    if (!_data["sounds"].isArray())
        throw std::exception("SoundComponent: sounds is not an array");

    auto sounds = _data["sounds"];
    const int soundsSize = sounds.size();
    for (int i = 0; i < soundsSize; ++i) {
        if (!sounds[i].isString()) {
            const std::string str = "SoundComponent: sounds[" +
                                    std::to_string(i) + "] is not an array";
            throw std::exception(str.c_str());
        }
        soundComponent->addSoundToList(sounds[i].asString());
    }

    return soundComponent;
}

DEFINE_FACTORY(SoundComponent);