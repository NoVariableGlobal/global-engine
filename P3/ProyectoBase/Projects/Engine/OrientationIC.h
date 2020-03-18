#pragma once
#include "InputComponent.h"
class OrientationIC :
	public InputComponent
{
private:
	float _orientation;
public:
	OrientationIC() = default;
	~OrientationIC() = default;
	void handleInput(const SDL_Event& _event);
	void setOrientation(float orientation);
};

