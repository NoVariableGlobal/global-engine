#pragma once
#include <fmod.hpp>
#include <list>
#include <map>
#include <string>


class Channel {
    FMOD::Channel* channel_;

public:
    Channel(FMOD::Channel* channel);
  FMOD::Channel* getChannel();
};




struct SoundInfo {
    std::string id_;
    std::string filename_;
    bool loop;
};

class SoundContext {
    static SoundContext* instance_;

    SoundContext();
    ~SoundContext();
    void releaseSoundInfo();

    static void ERRCHECK(FMOD_RESULT result);

    FMOD::System* system_ = nullptr;

    std::map<std::string, FMOD::Sound*> sounds_;
    std::list<SoundInfo>* soundsToLoad_;

  public:
    static SoundContext* getInstance();
    void init();

    FMOD::Sound* getSound(const std::string& id);
    Channel* playSound(FMOD::Sound* sound) const;
    void stopSound(Channel** channel);
};