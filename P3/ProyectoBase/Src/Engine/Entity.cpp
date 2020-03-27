#include "Entity.h"
#include "Component.h"
#include "Util.h"

Entity::Entity() {}

Entity::~Entity() {}

void Entity::addComponent(std::string name, Component* c) {
    components.insert({name, c});
}

Component* Entity::getComponent(std::string name) {
    return assert_find(components, name);
}

std::map<std::string, Component*>& Entity::getAllComponents() {
    return components;
}

std::string Entity::getId() { return id; }
void Entity::setId(std::string _id) { id = _id; }

void Entity::setActive(bool _active) {
    active = _active;
    for (auto c : components)
        c.second->setActive(active);
}

bool Entity::isActive() { return active; }
