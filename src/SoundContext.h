#pragma once
#include <fmod.hpp>
#include <map>
#include <string>
#include <list>

typedef FMOD::Sound Sound;
typedef FMOD::Channel Channel;

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
    std::list<SoundInfo> * _soundsToLoad;

public:
    static SoundContext* getInstance();
    void init();

    Sound* getSound(const std::string& id);
    Channel* playSound(Sound* sound) const;
    void stopSound(Channel** channel);

};