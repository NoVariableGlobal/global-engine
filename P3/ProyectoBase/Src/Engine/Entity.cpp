#include "Entity.h"
#include "Component.h"

Entity::Entity() {}

Entity::~Entity() {}

void Entity::addComponent(std::string name, Component* c) {
    components.insert({name, c});
}

Component* Entity::getComponent(std::string name) {
    return components.find(name)->second;
}

std::string Entity::getId() { return id; }
void Entity::setId(std::string _id) { id = _id; }

std::string Entity::getTag() { return tag; }
void Entity::setTag(std::string _tag) { tag = _tag; }

void Entity::setActive(bool _active) { 
    active = _active; 
    for (auto c : components)
        c.second->setActive(active);
}

bool Entity::isActive() { return active; }
