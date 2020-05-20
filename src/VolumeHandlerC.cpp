#include "VolumeHandlerC.h"
#include "Component.h"
#include "ComponentsManager.h"
#include "FactoriesFactory.h"
#include "Scene.h"
#include "SoundContext.h"

void VolumeHandlerComponent::updateFloat(float value) {
    SoundContext::getInstance()->setVolume(value);
}

float VolumeHandlerComponent::getFloat() {
    return SoundContext::getInstance()->getVolume();
}

// FACTORY INFRASTRUCTURE DEFINITION

VolumeHandlerComponentFactory::VolumeHandlerComponentFactory() = default;

Component* VolumeHandlerComponentFactory::create(Entity* _father,
                                                 Json::Value& _data,
                                                 Scene* _scene) {
    VolumeHandlerComponent* volumeHandlerComponent =
        new VolumeHandlerComponent();

    _scene->getComponentsManager()->addDC(volumeHandlerComponent);

    volumeHandlerComponent->setFather(_father);
    volumeHandlerComponent->setScene(_scene);

    return volumeHandlerComponent;
}

DEFINE_FACTORY(VolumeHandlerComponent);