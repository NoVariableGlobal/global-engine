#include "InputComponent.h"
#include "ComponentsManager.h"
#include "Scene.h"

InputComponent::InputComponent() : Component() {}

InputComponent::~InputComponent() {}

void InputComponent::destroy() {
    setActive(false);
    scene->getComponentsManager()->eraseIC(this);
}
