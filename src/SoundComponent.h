#pragma once
#include "Component.h"
#include "Factory.h"
#include <map>
#include <string>
// Sound es un objeto de la libreria de sonido

// FACTORY INFRASTRUCTURE DECLARATION
DECLARE_FACTORY(SoundComponent);
class Sound;
class Channel;

class SoundComponent : public Component {
    std::map<std::string, Channel*> channels_;

  public:
    SoundComponent();
    virtual ~SoundComponent();
    virtual void playSound(const std::string& id);
    virtual void stopSound(const std::string& id);
    virtual void destroy();
    virtual void addSoundToList(const std::string& id);
};