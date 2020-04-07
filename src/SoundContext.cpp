#include "SoundContext.h"
#include "fmod.h"
#include "fmod_errors.h"
#include <iostream>

SoundContext* SoundContext::instance_ = nullptr;

SoundContext::SoundContext() {
    sounds_ = std::map<std::string, FMOD::Sound*>();
    soundsToLoad_ = new std::list<SoundInfo*>();
}

SoundContext::~SoundContext() {
    releaseSoundInfo();
    for (auto it = sounds_.begin(); it != sounds_.end(); ++it)
        it->second->release();
    auto result = system_->release();
    ERRCHECK(result);
}

void SoundContext::releaseSoundInfo() {
    for (auto it = soundsToLoad_->begin(); it != soundsToLoad_->end(); ++it)
        delete *it;
    delete soundsToLoad_;
    soundsToLoad_ = nullptr;
}

void SoundContext::ERRCHECK(FMOD_RESULT result) {
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
    auto result = FMOD::System_Create(&system_);
    ERRCHECK(result);

    try {
        result = system_->init(128, FMOD_INIT_NORMAL, 0);
        ERRCHECK(result);
        for (auto it = soundsToLoad_->begin(); it != soundsToLoad_->end();
             ++it) {
            FMOD_MODE mode = ((*it)->loop) ? FMOD_LOOP_NORMAL
                                           : (FMOD_DEFAULT | FMOD_LOOP_OFF);
            std::string path = "media/sounds/" + (*it)->filename_;
            system_->createSound(path.c_str(), mode, 0, &sounds_[(*it)->id_]);
            ERRCHECK(result);
        }
    } catch (std::exception& e) {
        result = system_->release();
        ERRCHECK(result);
        throw e;
    }
}

void SoundContext::addSoundToLoad(SoundInfo* info) {
    soundsToLoad_->push_back(info);
}

FMOD::Sound* SoundContext::getSound(const std::string& id) {
    return sounds_[id];
}

Channel* SoundContext::playSound(FMOD::Sound* sound) const {
    FMOD::Channel* channel;
    try {
        auto result = system_->playSound(sound, 0, false, &channel);
        ERRCHECK(result);
        return new Channel(channel);
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        return nullptr;
    }
}

void SoundContext::stopSound(Channel** channel) {
    FMOD_RESULT result;
    try {
        result = (*channel)->getChannel()->stop();
        ERRCHECK(result);
        delete *channel;
        *channel = nullptr;
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        delete channel;
        *channel = nullptr;
    }
}

void SoundContext::updatePosition(Ogre::Vector3 _pos) {
    listenerPos_ = {_pos.x, _pos.y, _pos.z};
    FMOD_VECTOR vel = {0, 0, 0};
    FMOD_VECTOR forward = {0, 0, 1};
    FMOD_VECTOR up = {0, 1, 0};

    FMOD_RESULT result;

    try {
        result = system_->set3DListenerAttributes(0, &listenerPos_, &vel,
                                                  &forward, &up);
        ERRCHECK(result);
    } catch (std::exception& e) {
        result = system_->release();
        ERRCHECK(result);
        throw e;
    }
}

void SoundContext::update() {
    try {
        auto result = system_->update();
        ERRCHECK(result);
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}

Channel::Channel(FMOD::Channel* channel) : channel_(channel) {}

FMOD::Channel* Channel::getChannel() { return channel_; }