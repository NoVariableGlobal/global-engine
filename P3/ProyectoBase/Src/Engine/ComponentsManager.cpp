#include "ComponentsManager.h"
#include "PhysicsComponent.h"
#include "InputComponent.h"
#include "RenderComponent.h"
#include "SoundComponent.h"
#include "CameraComponent.h"


ComponentsManager::ComponentsManager()
{
}

ComponentsManager::~ComponentsManager()
{
	clearComponents();
}

void ComponentsManager::clearComponents()
{
	while (!physics.empty())
		physics.pop_back();

	while (!input.empty())
		input.pop_back();

	while (!rend.empty())
		rend.pop_back();

	while (!sound.empty())
		sound.pop_back();

	while (!camera.empty())
		camera.pop_back();
}

void ComponentsManager::addPC(PhysicsComponent* _physicsComponent)
{
	physics.push_back(_physicsComponent);
}

void ComponentsManager::deletePC(PhysicsComponent* _physicsComponent)
{
	bool erased = false;
	auto it = physics.begin();
	while (it != physics.end() && erased)
	{
		if ((*it) == _physicsComponent)
		{
			physics.erase(it);
			erased = true;
		}
		++it;
	}
}

void ComponentsManager::addIC(InputComponent* _inputComponent)
{
	input.push_back(_inputComponent);
}

void ComponentsManager::deleteIC(InputComponent* _inputComponent)
{
	bool erased = false;
	auto it = input.begin();
	while (it != input.end() && erased)
	{
		if ((*it) == _inputComponent)
		{
			input.erase(it);
			erased = true;
		}
		++it;
	}
}

void ComponentsManager::addRC(RenderComponent* _renderComponent)
{
	rend.push_back(_renderComponent);
}

void ComponentsManager::deleteRC(RenderComponent* _renderComponent)
{
	bool erased = false;
	auto it = rend.begin();
	while (it != rend.end() && erased)
	{
		if ((*it) == _renderComponent)
		{
			rend.erase(it);
			erased = true;
		}
		++it;
	}
}

void ComponentsManager::addSC(SoundComponent* _soundComponent)
{
	sound.push_back(_soundComponent);
}

void ComponentsManager::deleteSC(SoundComponent* _soundComponent)
{
	bool erased = false;
	auto it = sound.begin();
	while (it != sound.end() && erased)
	{
		if ((*it) == _soundComponent)
		{
			sound.erase(it);
			erased = true;
		}
		++it;
	}
}

void ComponentsManager::addCC(CameraComponent* _cameraComponent)
{
	camera.push_back(_cameraComponent);
}

void ComponentsManager::deleteCC(CameraComponent* _cameraComponent)
{
	bool erased = false;
	auto it = camera.begin();
	while (it != camera.end() && erased)
	{
		if ((*it) == _cameraComponent)
		{
			camera.erase(it);
			erased = true;
		}
		++it;
	}
}

void ComponentsManager::update()
{
	for (auto p : physics)
		p->update();
}

void ComponentsManager::handleInput()
{
	for (auto i : input)
		i->handleInput();
}

void ComponentsManager::render()
{
	for (auto r : rend)
		r->render();
}

void ComponentsManager::updateSound()
{
	// TO DO: updateSound method in SoundComponent
	/* for (auto s : sound)
		s->updateSound() */
}

void ComponentsManager::updateCamera()
{
	for (auto c : camera)
		c->updateCamera();
}
