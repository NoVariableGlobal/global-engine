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
    Entity* father_ = nullptr;

    // A pointer to the game scene
    Scene* scene_ = nullptr;
    bool active_ = true;

  public:
    Component();
    virtual ~Component();
    virtual void destroy() = 0;

    // Getters and setters
    bool isActive() const;
    virtual void setActive(bool active);
    void toggleActive();

    void setFather(Entity* father);
    Entity* getFather();

    void setScene(Scene* scene);
};
