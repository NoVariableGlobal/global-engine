#include "Entity.h"
#include "Component.h"
#include "Util.h"

void Entity::addComponent(const std::string& name, Component* c) {
    components_.insert({name, c});
}

Component* Entity::getComponent(const std::string& name) const {
    return assert_find(components_, name);
}

Component* Entity::findComponent(const std::string& name) const {
    return try_find(components_, name);
}

std::map<std::string, Component*>& Entity::getAllComponents() {
    return components_;
}

std::string Entity::getId() const { return id_; }
void Entity::setId(const std::string& id) { id_ = id; }

const std::string& Entity::getTag() const { return tag_; }

void Entity::setTag(const std::string& tag) { tag_ = tag; }

void Entity::setActive(const bool active) {
    active_ = active;
    for (auto c : components_)
        c.second->setActive(active_);
}

bool Entity::isActive() const { return active_; }

void Entity::setAsleep(const bool active) {
    asleep_ = active;
    for (auto c : components_)
        if (c.first != "TridimensionalObjectRC" && c.first != "RigidbodyPC")
            c.second->setActive(!asleep_);
}

bool Entity::isAsleep() const { return asleep_; }

void Entity::setPersistent(const bool p) { persistent_ = p; }

bool Entity::isPersistent() const { return persistent_; }
