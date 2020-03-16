#pragma once
#include "InputComponent.h"

namespace Ogre {
	typedef float Real;
	template <int dims, typename T> class Vector;
	typedef Vector<3, Real> Vector3;
}

class PlayerMovementIC : public InputComponent
{
private:
	float _speed;
public:
	PlayerMovementIC();
	virtual ~PlayerMovementIC();
	virtual void handleInput(const SDL_Event& _event);

	void setMovementSpeed(float speed);
};

