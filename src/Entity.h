#pragma once
#include <map>
#include <string>

class Component;

class Entity {

  private:
    // Shows if the entity is active or not
    bool active = false;
    // Whether or not the entity should persist between scenes
    bool persistent = false;
    // ID attached to the entity
    std::string id = "";
    // TAG attached to the entity
    std::string tag = "Default";
    // List of components attached to the entity
    std::map<std::string, Component*> components;

  public:
    Entity();
    virtual ~Entity();

    // Adds the component to the entity's list of components and to the
    // Component Manager's
    void addComponent(std::string name, Component* c);

    // Returns a component that is expected to exist, throws exception if not
    Component* getComponent(std::string name);

    // Returns the specified component or nullptr if it can't find it
    Component* findComponent(std::string name);

    std::map<std::string, Component*>& getAllComponents();
    // Getters and Setters
    std::string getId();
    void setId(std::string _id);

    const std::string& getTag() const;
    void setTag(const std::string& _tag);

    void setActive(bool _active);
    bool isActive();

    void setPersistent(bool _p);
    bool isPersistent();
};