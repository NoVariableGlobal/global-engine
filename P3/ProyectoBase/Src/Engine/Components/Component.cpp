#include "Component.h"

// Constructor
Component::Component() {}

// Destructor
Component::~Component() {}

// Returns true if the component is active, false otherwise
bool Component::isActive() { return _active; }

// Sets whether or not the component should update
void Component::setActive(bool a) { _active = a; }

// Activates the component if it is deactivated, deactivates it otherwise
void Component::toggleActive() { _active = !_active; }

void Component::setFather(Entity* father) { _father = father; }
