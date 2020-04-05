#include "SoundComponent.h"
#include "SoundContext.h"

SoundComponent::SoundComponent() {
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
