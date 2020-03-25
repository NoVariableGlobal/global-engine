#pragma once
#include <map>
#include <string>

class Component;

class Entity {

  private:
    // Shows if the entity is active or not
    bool active = false;
    // ID attached to the entity
    std::string id;
    // List of components attached to the entity
    std::map<std::string, Component*> components;

  public:
    Entity();
    virtual ~Entity();

    // Adds the component to the entity's list of components and to the
    // Component Manager's
    void addComponent(std::string name, Component* c);
    Component* getComponent(std::string name);
    std::map<std::string, Component*>& getAllComponents();
    // Getters and Setters
    std::string getId();
    void setId(std::string _id);

    void setActive(bool _active);
    bool isActive();
};