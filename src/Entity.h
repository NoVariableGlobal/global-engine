#pragma once
#include <map>
#include <string>

class Component;

class Entity {

    // Shows if the entity is active or not
    bool active_ = false;
    // Shows if the entity is asleep or not
    bool asleep_ = false;
    // Whether or not the entity should persist between scenes
    bool persistent_ = false;
    // ID attached to the entity
    std::string id_ = "";
    // TAG attached to the entity
    std::string tag_ = "Default";
    // List of components attached to the entity
    std::map<std::string, Component*> components_;

  public:
    // Adds the component to the entity's list of components and to the
    // Component Manager's
    void addComponent(const std::string& name, Component* c);

    // Returns a component that is expected to exist, throws exception if not
    Component* getComponent(const std::string& name) const;

    // Returns the specified component or nullptr if it can't find it
    Component* findComponent(const std::string& name) const;

    std::map<std::string, Component*>& getAllComponents();
    // Getters and Setters
    std::string getId() const;
    void setId(const std::string& id);

    const std::string& getTag() const;
    void setTag(const std::string& tag);

    void setActive(bool active);
    bool isActive() const;

    void setAsleep(bool active);
    bool isAsleep() const;

    void setPersistent(bool p);
    bool isPersistent() const;
};