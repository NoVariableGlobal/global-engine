#pragma once

// Sound es un objeto de la libreria de sonido
class Sound;

class SoundComponent /* : virtual public Component */ {
  public:
    SoundComponent();
    virtual ~SoundComponent();
    virtual void playSound(Sound* sound, bool loop);
    virtual void update() = 0;
};