#include "Component.h"

// Constructor
Component::Component() {}

// Destructor
Component::~Component() {}

// Returns true if the component is active, false otherwise
bool Entity::isActive() { return active; }

// Sets whether or not the component should update
void Entity::setActive(bool a) { active = a; }

// Activates the component if it is deactivated, deactivates it otherwise
bool Entity::toggleActive() { active = !active; }