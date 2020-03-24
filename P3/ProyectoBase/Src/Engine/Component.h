#pragma once
/*
        This is an abstract superclass from which every
        engine component or game component should inherit
*/

class Entity;
class Scene;

class Component {
  private:
    // Whether or not the component should be updated
    bool active = true;

  protected:
    // A pointer to the entity that has the component attached
    Entity* father = nullptr;

    // A pointer to the game scene
    Scene* scene = nullptr;

  public:
    Component();
    virtual ~Component();
    virtual void destroyMyself() = 0;

    // Getters and setters
    bool isActive();
    virtual void setActive(bool active);
    void toggleActive();

    void setFather(Entity* father);
    void setScene(Scene* scene);
};