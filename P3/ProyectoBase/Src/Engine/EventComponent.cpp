#include "EventComponent.h"
#include "ComponentsManager.h"
#include "Scene.h"

EventComponent::EventComponent() {}

EventComponent::~EventComponent() {}

void EventComponent::destroy() {
    setActive(false);
    scene->getComponentsManager()->eraseEC(this);
}
