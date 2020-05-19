#include "VolumeHandlerC.h"
#include "SoundContext.h"
#include "FactoriesFactory.h"
#include "ComponentsManager.h"
#include "Scene.h"
#include "Component.h"

void VolumeHandlerComponent::updateFloat(float value) {
    SoundContext::getInstance()->setVolume(value);
}

// FACTORY INFRASTRUCTURE DEFINITION

VolumeHandlerComponentFactory::VolumeHandlerComponentFactory() = default;

Component* VolumeHandlerComponentFactory::create(Entity* _father,
                                                 Json::Value& _data,
                                                 Scene* _scene) {
    VolumeHandlerComponent* volumeHandlerComponent =
        new VolumeHandlerComponent();


    volumeHandlerComponent->setFather(_father);
    volumeHandlerComponent->setScene(_scene);
   

    return volumeHandlerComponent;
}

DEFINE_FACTORY(VolumeHandlerComponent);