#pragma once
#include <OgreVector3.h>
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
    bool loop_;
    float volume_;
};

class SoundContext {
    static SoundContext* instance_;

    SoundContext();
    ~SoundContext();
    void releaseSoundInfo();

    static void ERRCHECK(FMOD_RESULT result);

    FMOD::System* system_ = nullptr;

    std::map<std::string, FMOD::Sound*> sounds_;
    std::map<std::string, SoundInfo*>* soundsToLoad_;
    FMOD_VECTOR listenerPos_;

  public:
    static SoundContext* getInstance();
    static void destroy();
    void init();

    void addSoundToLoad(SoundInfo* info);

    FMOD::Sound* getSound(const std::string& id);
    Channel* playSound(const std::string& id) const;
    void stopSound(Channel** channel);
    void updatePosition(Ogre::Vector3 pos);
    void update();
};