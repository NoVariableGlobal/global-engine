#include "BrightnessHandlerC.h"
#include <SDL.h>

#include "ComponentsManager.h"
#include "FactoriesFactory.h"
#include "OgreSDLContext.h"
#include "Scene.h"

void BrightnessHandlerComponent::updateFloat(float value) {
    SDL_SetWindowBrightness(OgreSDLContext::getInstance()->getSDLWindow(),
                            value);
}

float BrightnessHandlerComponent::getFloat() {
    return SDL_GetWindowBrightness(
        OgreSDLContext::getInstance()->getSDLWindow());
}

// FACTORY INFRASTRUCTURE DEFINITION

BrightnessHandlerComponentFactory::BrightnessHandlerComponentFactory() =
    default;

Component* BrightnessHandlerComponentFactory::create(Entity* _father,
                                                     Json::Value& _data,
                                                     Scene* _scene) {
    BrightnessHandlerComponent* brightnessHandlerComponent =
        new BrightnessHandlerComponent();

    _scene->getComponentsManager()->addDC(brightnessHandlerComponent);

    brightnessHandlerComponent->setFather(_father);
    brightnessHandlerComponent->setScene(_scene);

    return brightnessHandlerComponent;
}

DEFINE_FACTORY(BrightnessHandlerComponent);
