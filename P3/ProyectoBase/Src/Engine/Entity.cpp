#include "Entity.h"

Entity::~Entity() {}

void Entity::addComponent(Component* c) {
	components.push_back(c);
	// Registrar componente en el manager
}

bool Entity::isActive() { return active; }
void Entity::setActive(bool a) { active = a; }
bool Entity::toggleActive() { active = !active; }

Vector3 Entity::getScale() { return scale; }
void Entity::setScale(Vector3 s) { scale = s; }

Vector3 Entity::getPosition() { return position; }
void Entity::setPosition(Vector3 p) { position = p; }

Vector3 Entity::getRotation() { return rotation; }
void Entity::setRotation(Vector3 r) { rotation = r; }