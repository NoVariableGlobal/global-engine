#include "SoundContext.h"
#include "fmod.h"
#include "fmod_errors.h"
#include <Ogre.h>
#include <cstdlib>
#include <iostream>

SoundContext* SoundContext::instance_ = nullptr;

SoundContext::SoundContext() {
    sounds_ = std::map<std::string, FMOD::Sound*>();
    soundsToLoad_ = new std::map<std::string, SoundInfo*>();
    listenerPos_ = {0.0f, 0.0f, 0.0f};
}

SoundContext::~SoundContext() {
    releaseSoundInfo();
    for (auto it = sounds_.begin(); it != sounds_.end(); ++it)
        it->second->release();

    const auto result = system_->release();
    checkError(result);
}

void SoundContext::releaseSoundInfo() {
    for (auto it = soundsToLoad_->begin(); it != soundsToLoad_->end(); ++it)
        delete it->second;
    delete soundsToLoad_;
    soundsToLoad_ = nullptr;
}

void SoundContext::checkError(const FMOD_RESULT result) {
    if (result != FMOD_OK)
        throw std::exception(FMOD_ErrorString(result));
}

SoundContext* SoundContext::getInstance() {
    if (instance_ == nullptr)
        instance_ = new SoundContext();
    return instance_;
}

void SoundContext::destroy() {
    delete instance_;
    instance_ = nullptr;
}

void SoundContext::init() {
    auto result = System_Create(&system_);
    checkError(result);

    try {
        result = system_->init(128, FMOD_INIT_NORMAL, nullptr);
        checkError(result);
        for (auto it = soundsToLoad_->begin(); it != soundsToLoad_->end();
             ++it) {
            const FMOD_MODE mode = it->second->loop
                                       ? FMOD_LOOP_NORMAL
                                       : (FMOD_DEFAULT | FMOD_LOOP_OFF);
            std::string path = "media/sounds/" + it->second->filename;
            system_->createSound(path.c_str(), mode, nullptr,
                                 &sounds_[it->second->id]);
            checkError(result);

            result = system_->getMasterChannelGroup(&masterGroup_);
            checkError(result);
        }
    } catch (std::exception&) {
        result = system_->release();
        checkError(result);
        throw;
    }
}

void SoundContext::addSoundToLoad(SoundInfo* info) {
    (*soundsToLoad_)[info->id] = info;
}

Channel* SoundContext::playSound(const std::string& id) const {
    FMOD::Channel* channel = nullptr;
    try {
        auto result = system_->playSound(getInstance()->getSound(id), nullptr,
                                         true, &channel);
        checkError(result);
        const float volume = (*soundsToLoad_)[id]->volume;
        if (abs(volume - 1.0) > 0.001) {
            result = channel->setVolume(volume);
            checkError(result);
        }

        result = channel->setPaused(false);
        checkError(result);
        return new Channel(channel);
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        return nullptr;
    }
}

FMOD::Sound* SoundContext::getSound(const std::string& id) {
    return sounds_[id];
}

void SoundContext::stopSound(Channel** channel) {
    try {
        const FMOD_RESULT result = (*channel)->getChannel()->stop();
        checkError(result);
        delete *channel;
        *channel = nullptr;
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        delete channel;
        *channel = nullptr;
    }
}

void SoundContext::updatePosition(const Ogre::Vector3 pos) {
    listenerPos_ = {pos.x, pos.y, pos.z};
    FMOD_VECTOR vel = {0, 0, 0};
    FMOD_VECTOR forward = {0, 0, 1};
    FMOD_VECTOR up = {0, 1, 0};

    FMOD_RESULT result;

    try {
        result = system_->set3DListenerAttributes(0, &listenerPos_, &vel,
                                                  &forward, &up);
        checkError(result);
    } catch (std::exception& e) {
        result = system_->release();
        checkError(result);
        throw;
    }
}

void SoundContext::update() {
    try {
        const auto result = system_->update();
        checkError(result);
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}

void SoundContext::setVolume(float volume) const {
    try {
        const auto result = masterGroup_->setVolume(volume);
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}

const float SoundContext::getVolume() const {
    float volume;
    try {
        const auto result = masterGroup_->getVolume(&volume);
        return volume;
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 0;
    }
}

Channel::Channel(FMOD::Channel* channel) : channel_(channel) {}

FMOD::Channel* Channel::getChannel() const { return channel_; }
