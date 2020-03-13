#pragma once
#include "InputComponent.h"
class TopDownPlayerMovementIC : public InputComponent
{
private:
	float _speed;
public:
	TopDownPlayerMovementIC();
	virtual ~TopDownPlayerMovementIC();
	virtual void handleInput(const SDL_Event& _event);

	void setMovementSpeed(float speed);
};

