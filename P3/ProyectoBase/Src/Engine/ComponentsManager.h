#pragma once

#include <list>
class InputComponent;
class PhysicsComponent;
class RenderComponent;
class CameraComponent;
class SoundComponent;

class ComponentsManager
{
private:
	std::list<InputComponent*> input;
	std::list<PhysicsComponent*> physics;
	std::list<RenderComponent*> rend;
	std::list<CameraComponent*> camera;
	std::list<SoundComponent*> sound;
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

	// add camera component to list
	void addCC(CameraComponent* _cameraComponent);
	// delete camera component from list
	void deleteCC(CameraComponent* _cameraComponent);

	// call each physics component in the list
	void update();
	// call each input component in the list
	void handleInput();
	// call each render component in the list
	void render();
	// call each sound component in the list
	void updateSound();
	// call each camera component in the list
	void updateCamera();
};

