#include "Component.h"

// Constructor
Component::Component() = default;

// Destructor
Component::~Component() = default;

// Returns true if the component is active, false otherwise
bool Component::isActive() const { return active_; }

// Sets whether or not the component should update
void Component::setActive(const bool active) { active_ = active; }

// Activates the component if it is deactivated, deactivates it otherwise
void Component::toggleActive() { active_ = !active_; }

void Component::setFather(Entity* father) { father_ = father; }
Entity* Component::getFather() { return father_; }

void Component::setScene(Scene* scene) { scene_ = scene; }
