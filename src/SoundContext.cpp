#include "SoundContext.h"

#include "fmod_errors.h"
#include <iostream>

SoundContext* SoundContext::instance_ = nullptr;

SoundContext::SoundContext() {
    sounds_ = std::map<std::string, FMOD::Sound*>();
    soundsToLoad_ = new std::list<SoundInfo>();
}

SoundContext::~SoundContext() {
    system_->release();
    releaseSoundInfo();

}

void SoundContext::releaseSoundInfo() {
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

void SoundContext::init() {
    auto result = System_Create(&system_);
    ERRCHECK(result);

    try {
        result = system_->init(128, FMOD_INIT_NORMAL, 0);
        ERRCHECK(result);
        for (auto it = soundsToLoad_->begin(); it != soundsToLoad_->end();
             ++it) {

            FMOD_MODE mode = (it->loop) ? FMOD_LOOP_NORMAL : (FMOD_DEFAULT | FMOD_LOOP_OFF);

            system_->createSound(it->filename_.c_str(), mode, 0,
                                 &sounds_[it->id_]);
            ERRCHECK(result);
        }
    } catch (std::exception& e) {
        result = system_->release();
        ERRCHECK(result);
        throw e;
    }

}


FMOD::Sound* SoundContext::getSound(const std::string& id) { return sounds_[id]; }

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
        delete channel;
        *channel = nullptr;
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        delete channel;
        *channel = nullptr;
    }
}

Channel::Channel(FMOD::Channel* channel) : channel_(channel){}
