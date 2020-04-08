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

Component* Entity::findComponent(std::string name) {
    return try_find(components, name);
}

std::map<std::string, Component*>& Entity::getAllComponents() {
    return components;
}

std::string Entity::getId() { return id; }
void Entity::setId(std::string _id) { id = _id; }

const std::string& Entity::getTag() const { return tag; }

void Entity::setTag(const std::string& _tag) { tag = _tag; }

void Entity::setActive(bool _active) {
    active = _active;
    for (auto c : components)
        c.second->setActive(active);
}

bool Entity::isActive() { return active; }

void Entity::setAsleep(bool _active) {
    asleep = _active;
    for (auto c : components)
        if (c.first != "TridimensionalObjectRC" && c.first != "RigidbodyPC")
            c.second->setActive(!asleep);
}

bool Entity::isAsleep() { return asleep; }

void Entity::setPersistent(bool _p) { persistent = _p; }

bool Entity::isPersistent() { return persistent; }
