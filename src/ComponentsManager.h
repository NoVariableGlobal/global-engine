#pragma once

#include <vector>

#include <Ogre.h>
#include <SDL_events.h>

class InputComponent;
class PhysicsComponent;
class RenderComponent;
class SoundComponent;
class Component;
class EventComponent;
class ListenerComponent;

class ComponentsManager final : public Ogre::FrameListener {
    // vectors for each component type
    std::vector<InputComponent*> input_;
    std::vector<PhysicsComponent*> physics_;
    std::vector<RenderComponent*> rend_;
    std::vector<SoundComponent*> sound_;
    std::vector<Component*> deleteable_;
    std::vector<EventComponent*> event_;
    std::vector<ListenerComponent*> listener_;

    std::vector<InputComponent*> deleteInput_;
    std::vector<PhysicsComponent*> deletePhysics_;
    std::vector<RenderComponent*> deleteRend_;
    std::vector<SoundComponent*> deleteSound_;
    std::vector<Component*> deleteDeleteable_;
    std::vector<EventComponent*> deleteEvent_;
    std::vector<ListenerComponent*> deleteListener_;

    std::vector<InputComponent*> insertInput_;
    std::vector<PhysicsComponent*> insertPhysics_;
    std::vector<RenderComponent*> insertRend_;
    std::vector<SoundComponent*> insertSound_;
    std::vector<Component*> insertDeleteable_;
    std::vector<EventComponent*> insertEvent_;
    std::vector<ListenerComponent*> insertListener_;

  public:
    ComponentsManager();
    ~ComponentsManager();

    // removes all components from all vectors
    void clearComponents();

    // add physics component to vector
    void addPC(PhysicsComponent* physicsComponent);
    // add physics component to insert
    void insertPC();
    // delete physics component from vector
    void deletePC();
    // add physic component to delete vector
    void erasePC(PhysicsComponent* physicsComponent);

    // add input component to vector
    void addIC(InputComponent* inputComponent);
    // add input component to insert
    void insertIC();
    // delete input component from vector
    void deleteIC();
    // add input component to delete vector
    void eraseIC(InputComponent* inputComponent);

    // add render component to vector
    void addRC(RenderComponent* renderComponent);
    // add render component to insert
    void insertRC();
    // delete render component from vector
    void deleteRC();
    // add render component to delete vector
    void eraseRC(RenderComponent* renderComponent);

    // add sound component to vector
    void addSC(SoundComponent* soundComponent);
    // add sound component to insert
    void insertSC();
    // delete sound component from vector
    void deleteSC();
    // add sound component to delete vector
    void eraseSC(SoundComponent* soundComponent);

    // add deleteable component to vector
    void addDC(Component* deleteableComponent);
    // add deleteable component to insert
    void insertDC();
    // delete deleteable component from vector
    void deleteDC();
    // add deletable component to delete vector
    void eraseDC(Component* deleteableComponent);

    // add event component to vector
    void addEC(EventComponent* eventComponent);
    // add event component to insert
    void insertEC();
    // delete event component from vector
    void deleteEC();
    // add event component to delete vector
    void eraseEC(EventComponent* eventComponent);

    // add listener component to vector
    void addLC(ListenerComponent* listenerComponent);
    // add listener component to insert
    void insertLC();
    // delete listener component from vector
    void deleteLC();
    // add listener component to delete vector
    void eraseLC(ListenerComponent* listenerComponent);

    // call each physics component in the vector
    void update();
    // call each input component in the vector
    void handleInput(const SDL_Event& event);
    // call each render component in the vector
    void render();
    // call each sound component in the vector
    void updateSound();
    // call each event component in the vector
    void updateEvent();
    // call each listener component in the vector
    bool frameRenderingQueued(const Ogre::FrameEvent& _event) override;

    // delete all the components to delete
    void deleteComponents();
    // insert all the components to insert
    void insertComponents();
};
