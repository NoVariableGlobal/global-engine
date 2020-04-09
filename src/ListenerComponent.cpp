#include "ListenerComponent.h"
#include "ComponentsManager.h"
#include "Scene.h"

ListenerComponent::ListenerComponent() : Component() {}

ListenerComponent::~ListenerComponent() {}

void ListenerComponent::destroy() {
    setActive(false);
    scene->getComponentsManager()->eraseLC(this);
}
