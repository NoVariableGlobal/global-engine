#pragma once
#include <vector>
class InputComponent;
class PhysicsComponent;
class RenderComponent;
class SoundComponent;
class Component;

class ComponentsManager
{
private:
	std::vector<InputComponent*> input;
	std::vector<PhysicsComponent*> physics;
	std::vector<RenderComponent*> rend;
	std::vector<SoundComponent*> sound;
	std::vector<Component*> tran;
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

	// add sound component to list
	void addTC(Component* _transformComponent);
	// delete sound component from list
	void deleteTC(Component* _transformComponent);

	// call each physics component in the list
	void update();
	// call each input component in the list
	void handleInput();
	// call each render component in the list
	void render();
	// call each sound component in the list
	void updateSound();
};

