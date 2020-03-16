#pragma once

#include <vector>

#include <SDL_events.h>

class InputComponent;
class PhysicsComponent;
class RenderComponent;
class SoundComponent;
class Component;
class EventComponent;

class ComponentsManager
{
private:
	std::vector<InputComponent*> input;
	std::vector<PhysicsComponent*> physics;
	std::vector<RenderComponent*> rend;
	std::vector<SoundComponent*> sound;
	std::vector<Component*> deleteable;
	std::vector<EventComponent*> event;
public:
	ComponentsManager();
	~ComponentsManager();

	void clearComponents();

	// add physics component to list
	void addPC(PhysicsComponent* _physicsComponent);
	// delete physics component from list
	void deletePC(PhysicsComponent* _physicsComponent);

	// add input component to list
	void addIC(InputComponent* _inputComponent);
	// delete input component from list
	void deleteIC(InputComponent* _inputComponent);

	// add render component to list
	void addRC(RenderComponent* _renderComponent);
	// delete render component from list
	void deleteRC(RenderComponent* _renderComponent);

	// add sound component to list
	void addSC(SoundComponent* _soundComponent);
	// delete sound component from list
	void deleteSC(SoundComponent* _soundComponent);
  
	// add deleteable component to list
	void addDC(Component* _deleteableComponent);
	// delete deleteable component from list
	void deleteDC(Component* _deleteableComponent);

	// add event component to list
	void addEC(EventComponent* _eventComponent);
	// delete event component from list
	void deleteEC(EventComponent* _eventComponent);

	// call each physics component in the list
	void update();
	// call each input component in the list
	void handleInput(const SDL_Event& _event);
	// call each render component in the list
	void render();
	// call each sound component in the list
	void updateSound();
	// call each event component in the list
	void updateEvent();
};

