#include "PhysicsComponent.h"
#include "ComponentsManager.h"
#include "Scene.h"

void PhysicsComponent::destroy() {
    setActive(false);
    scene_->getComponentsManager()->erasePC(this);
}
