#include "ComponentsManager.h"
#include "PhysicsComponent.h"
#include "InputComponent.h"
#include "RenderComponent.h"
#include "SoundComponent.h"
#include "CameraComponent.h"


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
