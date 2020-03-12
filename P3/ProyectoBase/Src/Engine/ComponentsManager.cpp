#include "ComponentsManager.h"
#include "PhysicsComponent.h"
#include "InputComponent.h"
#include "SoundComponent.h"
#include "RenderComponent.h"
#include "EventComponent.h"


ComponentsManager::ComponentsManager()
{
}

ComponentsManager::~ComponentsManager()
{
	clearComponents();
}

void ComponentsManager::clearComponents()
{
	int size = physics.size();
	for (int i = size - 1; i >= 0; i--)
	{
		delete physics[i];
		physics.pop_back();
	}

	size = input.size();
	for (int i = size - 1; i >= 0; i--)
	{
		delete input[i];
		input.pop_back();
	}

	size = rend.size();
	for (int i = size - 1; i >= 0; i--)
	{
		delete rend[i];
		rend.pop_back();
	}

	size = sound.size();
	for (int i = size - 1; i >= 0; i--)
	{
		delete sound[i];
		sound.pop_back();
	}

	size = event.size();
	for (int i = size - 1; i >= 0; i--)
	{
		delete event[i];
		event.pop_back();
	}

	size = deleteable.size();
	for (int i = size - 1; i >= 0; i--)
	{
		delete deleteable[i];
		deleteable.pop_back();
	}
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

void ComponentsManager::addDC(Component* _deleteableComponent)
{
	deleteable.push_back(_deleteableComponent);
}

void ComponentsManager::deleteDC(Component* _deleteableComponent)
{
	bool erased = false;
	auto it = deleteable.begin();
	while (it != deleteable.end() && erased)
	{
		if ((*it) == _deleteableComponent)
		{
			deleteable.erase(it);
			erased = true;
		}
		++it;
	}
}

void ComponentsManager::addEC(EventComponent* _eventComponent)
{
	event.push_back(_eventComponent);
}

void ComponentsManager::deleteEC(EventComponent* _eventComponent)
{
	bool erased = false;
	auto it = event.begin();
	while (it != event.end() && erased)
	{
		if ((*it) == _eventComponent)
		{
			event.erase(it);
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

void ComponentsManager::updateEvent()
{
	for (auto r : event)
		r->checkEvent();
}