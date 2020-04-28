#include "EventComponent.h"
#include "ComponentsManager.h"
#include "Scene.h"

void EventComponent::destroy() {
    setActive(false);
    scene_->getComponentsManager()->eraseEC(this);
}
