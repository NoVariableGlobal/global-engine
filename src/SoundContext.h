#pragma once
#include <fmod.hpp>
#include <map>
#include <string>

namespace Ogre {
    typedef float Real;
    template <int Dims, typename T> class Vector;
    typedef Vector<3, Real> Vector3;
} // namespace Ogre

class Channel {
    FMOD::Channel* channel_;

  public:
    explicit Channel(FMOD::Channel* channel);
    FMOD::Channel* getChannel() const;
};

struct SoundInfo {
    std::string id;
    std::string filename;
    bool loop;
    float volume;
};

class SoundContext {
    static SoundContext* instance_;

    SoundContext();
    ~SoundContext();
    void releaseSoundInfo();

    static void checkError(FMOD_RESULT result);

    FMOD::System* system_ = nullptr;
    FMOD::ChannelGroup* masterGroup_ = nullptr;
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
    void setVolume(float volume) const;
    const float getVolume() const;
};