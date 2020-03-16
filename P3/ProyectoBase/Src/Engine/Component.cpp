#include "Component.h"

// Constructor
Component::Component() {}

// Destructor
Component::~Component() {}

// Returns true if the component is active, false otherwise
bool Component::isActive() { return active; }

// Sets whether or not the component should update
void Component::setActive(bool _active) { active = _active; }

// Activates the component if it is deactivated, deactivates it otherwise
void Component::toggleActive() { active = !active; }

void Component::setFather(Entity* _father) { father = _father; }
void Component::setScene(Scene* _scene) { scene = _scene; }
