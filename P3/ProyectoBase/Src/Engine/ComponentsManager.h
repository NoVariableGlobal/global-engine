#pragma once

#include <vector>

#include <SDL_events.h>

class InputComponent;
class PhysicsComponent;
class RenderComponent;
class SoundComponent;
class Component;
class EventComponent;

class ComponentsManager {
  private:
    // vectors for each component type
    std::vector<InputComponent*> input;
    std::vector<PhysicsComponent*> physics;
    std::vector<RenderComponent*> rend;
    std::vector<SoundComponent*> sound;
    std::vector<Component*> deleteable;
    std::vector<EventComponent*> event;

    std::vector<InputComponent*> deleteInput;
    std::vector<PhysicsComponent*> deletePhysics;
    std::vector<RenderComponent*> deleteRend;
    std::vector<SoundComponent*> deleteSound;
    std::vector<Component*> deleteDeleteable;
    std::vector<EventComponent*> deleteEvent;

  public:
    ComponentsManager();
    ~ComponentsManager();

    // removes all components from all vectors
    void clearComponents();

    // add physics component to vector
    void addPC(PhysicsComponent* _physicsComponent);
    // delete physics component from vector
    void deletePC();
    // add physic component to delete vector
    void erasePC(PhysicsComponent* _physicsComponent);

    // add input component to vector
    void addIC(InputComponent* _inputComponent);
    // delete input component from vector
    void deleteIC();
    // add input component to delete vector
    void eraseIC(InputComponent* _inputComponent);

    // add render component to vector
    void addRC(RenderComponent* _renderComponent);
    // delete render component from vector
    void deleteRC();
    // add render component to delete vector
    void eraseRC(RenderComponent* _renderComponent);

    // add sound component to vector
    void addSC(SoundComponent* _soundComponent);
    // delete sound component from vector
    void deleteSC();
    // add sound component to delete vector
    void eraseSC(SoundComponent* _soundComponent);

    // add deleteable component to vector
    void addDC(Component* _deleteableComponent);
    // delete deleteable component from vector
    void deleteDC();
    // add deletable component to delete vector
    void eraseDC(Component* _deleteableComponent);

    // add event component to vector
    void addEC(EventComponent* _eventComponent);
    // delete event component from vector
    void deleteEC();
    // add event component to delete vector
    void eraseEC(EventComponent* _eventComponent);

    // call each physics component in the vector
    void update();
    // call each input component in the vector
    void handleInput(const SDL_Event& _event);
    // call each render component in the vector
    void render();
    // call each sound component in the vector
    void updateSound();
    // call each event component in the vector
    void updateEvent();
    // delete all the components to delete
    void deleteComponents();
};
