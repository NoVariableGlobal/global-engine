#include "Entity.h"
#include "Component.h"

#include <iostream>

Entity::Entity() {}

Entity::~Entity() {}

void Entity::addComponent(std::string name, Component* c) {
    components.insert({name, c});
}

Component* Entity::getComponent(std::string name) {
    auto it = components.find(name);
    if (it == components.end()) {
        std::cout << "ERROR: Component '" + name + "' could not be found\n";
        throw std::exception("Component could not be found");
    }
    return it->second;
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
