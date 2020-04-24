#include "ListenerComponent.h"
#include "ComponentsManager.h"
#include "Scene.h"

void ListenerComponent::destroy() {
    setActive(false);
    scene_->getComponentsManager()->eraseLC(this);
}
