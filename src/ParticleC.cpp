#include "ParticleC.h"
#include "ComponentsManager.h"
#include "Entity.h"
#include "FactoriesFactory.h"
#include "OgreSDLContext.h"
#include "Scene.h"
#include "TridimensionalObjectRC.h"

#include <Ogre.h>
#include <OgreAnimationState.h>
#include <json.h>

void ParticleC::destroy() {
    clearParticleSystems();
    setActive(false);
    scene_->getComponentsManager()->eraseDC(this);
}

void ParticleC::emitParticles(const std::string& name) {
    particles_.find(name)->second->setEmitting(true);
}

void ParticleC::stopAllParticles() {
    for (auto part : particles_)
        if (part.second->getEmitting()) {
            part.second->setEmitting(false);
        }
}

void ParticleC::stopParticles(const std::string& name) {
    particles_.find(name)->second->setEmitting(false);
}

void ParticleC::addParticle(const std::string& name,
                            const std::string& particleName) {

    Ogre::SceneManager* mSM = OgreSDLContext::getInstance()->getSceneManager();

    Ogre::ParticleSystem* newParticle =
        mSM->createParticleSystem(name, particleName);
    newParticle->setEmitting(false);

    auto* renderFather = reinterpret_cast<TridimensionalObjectRC*>(
        father_->getComponent("TridimensionalObjectRC"));
    renderFather->getSceneNode()->attachObject(newParticle);

    particles_.emplace(name, newParticle);
}

void ParticleC::clearParticleSystems() {
    Ogre::SceneManager* mSM = OgreSDLContext::getInstance()->getSceneManager();

    for (auto p : particles_) {
        mSM->destroyParticleSystem(p.second);
    }

    particles_.clear();
}

// FACTORY INFRASTRUCTURE
ParticleCFactory::ParticleCFactory() = default;

Component* ParticleCFactory::create(Entity* _father, Json::Value& _data,
                                    Scene* _scene) {
    auto* particles = new ParticleC();
    _scene->getComponentsManager()->addDC(particles);

    particles->setFather(_father);
    particles->setScene(_scene);

    if (_data["particles"].isArray()) {
        if (!_data["particles"][0].isObject())
            throw std::exception(
                "ParticleLC: particles is not an array of objects. Every "
                "object must have this structure: \n {\nname: "
                "string\particleName: "
                "string\n}");

        Json::Value array = _data["particles"];
        const int size = array.size();
        for (int i = 0; i < size; i++) {
            if (!array[i]["name"].isString() ||
                !array[i]["particleName"].isString())
                throw std::exception(
                    "ParticleC: name or particleName are not a string");
            particles->addParticle(array[i]["name"].asString(),
                                   array[i]["particleName"].asString());
        }
    }

    return particles;
};

DEFINE_FACTORY(ParticleC);
