#include "SoundContext.h"

#include "fmod_errors.h"
#include <iostream>

SoundContext* SoundContext::_instance = nullptr;

SoundContext::SoundContext() {
    _sounds = std::map<std::string, Sound*>();
    _soundsToLoad = new std::list<SoundInfo>();
}

void SoundContext::ERRCHECK(FMOD_RESULT result) {
    if (result != FMOD_OK)
        throw std::exception(FMOD_ErrorString(result));
}

SoundContext* SoundContext::getInstance() {
    if (_instance == nullptr)
        _instance = new SoundContext();
    return _instance;
}

void SoundContext::init() {
    auto result = System_Create(&_system);
    ERRCHECK(result);

    try {
        result = _system->init(128, FMOD_INIT_NORMAL, 0);
        ERRCHECK(result);
        for (auto it = _soundsToLoad->begin(); it != _soundsToLoad->end();
             ++it) {

            FMOD_MODE mode = (it->loop) ? FMOD_LOOP_NORMAL : (FMOD_DEFAULT | FMOD_LOOP_OFF);

            _system->createSound(it->_filename.c_str(), mode, 0,
                                 &_sounds[it->_id]);
            ERRCHECK(result);
        }
    } catch (std::exception& e) {
        result = _system->release();
        ERRCHECK(result);
        throw e;
    }

}

Sound* SoundContext::getSound(const std::string& id) { return _sounds[id]; }

Channel* SoundContext::playSound(Sound* sound) const {
    Channel* channel;
    try {
        auto result = _system->playSound(sound, 0, false, &channel);
        ERRCHECK(result);
        return channel;
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        return nullptr;
    }
}

void SoundContext::stopSound(Channel** channel) {
    FMOD_RESULT result;
    try {
        result = (*channel)->stop();
        ERRCHECK(result);
        *channel = nullptr;
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        *channel = nullptr;
    }

}

