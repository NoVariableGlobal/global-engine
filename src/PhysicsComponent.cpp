#include "PhysicsComponent.h"
#include "ComponentsManager.h"
#include "PhysicsContext.h"
#include "Scene.h"

PhysicsComponent::PhysicsComponent() {}

PhysicsComponent::~PhysicsComponent() {}

void PhysicsComponent::destroy() {
    setActive(false);
    scene->getComponentsManager()->erasePC(this);
}
