#pragma once
#include "Component.h"
#include "Factory.h"

#include <map>
#include <string>

namespace Ogre {
    class ParticleSystem;
}

DECLARE_FACTORY(ParticleC)

class ParticleC final : public Component {
    // id, particle
    std::map<std::string, Ogre::ParticleSystem*> particles_;

  public:
    // Destroys the ParticleC, setting itself as inactive and
    // removing itself from the scene.
    virtual void destroy();

    // active the specify particle
    void emitParticles(const std::string& name);
    // stop all the enabled particles
    void stopAllParticles();
    // stop the particle specified
    void stopParticles(const std::string& name);
    // add a particle to the map of particles
    void addParticle(const std::string& name, const std::string& particleName,
                     const std::string& attached);
    // destroy all the particle systems that exist in this component
    void destroyAllParticleSystem();
};
