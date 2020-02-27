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
	void update();
	void handleInput();
	void render();
	void updateSound();
	void updateCamera();
};

