#pragma once
#include <string>
#include <map>

// Sound es un objeto de la libreria de sonido

class Sound;
class Channel;

class SoundComponent /* : virtual public Component */ {
    std::map<std::string, Channel*> channels_; 

  public:
    SoundComponent();
    virtual ~SoundComponent();
    virtual void playSound(const std::string &id);
    virtual void update() = 0;
    virtual void stopSound(const std::string& id);
};