#include "InputComponent.h"
#include "ComponentsManager.h"
#include "Scene.h"

void InputComponent::destroy() {
    setActive(false);
    scene_->getComponentsManager()->eraseIC(this);
}
