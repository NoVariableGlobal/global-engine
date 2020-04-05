#pragma once
#include <fmod.h>
#include <fmod.hpp>
#include <map>
#include <string>
#include <list>

typedef FMOD::Sound Sound;

struct SoundInfo {
    std::string _id;
    std::string _filename;
    bool loop;
};

class SoundContext {
    static SoundContext* _instance;
    

    SoundContext();
    static void ERRCHECK(FMOD_RESULT result);

    FMOD::System* _system = nullptr;


    std::map<std::string, Sound*> _sounds;
    //std::map<std::string, FMOD::Channel*> _channels;
    std::list<SoundInfo> * _soundsToLoad;

public:
    static SoundContext* getInstance();
    void init();

    Sound* getSound(const std::string& id);
    void playSound(const Sound* sound);

};