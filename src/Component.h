#pragma once
/*
        This is an abstract superclass from which every
        engine component or game component should inherit
*/

class Entity;
class Scene;

class Component {

  protected:
    // A pointer to the entity that has the component attached
    Entity* father = nullptr;

    // A pointer to the game scene
    Scene* scene = nullptr;
    bool active = true;

  public:
    Component();
    virtual ~Component();
    virtual void destroy() = 0;

    // Getters and setters
    bool isActive();
    virtual void setActive(bool active);
    void toggleActive();

    Entity* getFather();
    void setFather(Entity* father);
    void setScene(Scene* scene);
};
