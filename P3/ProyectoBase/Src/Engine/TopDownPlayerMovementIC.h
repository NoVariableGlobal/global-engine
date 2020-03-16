#pragma once
#include "InputComponent.h"

namespace Ogre {
	typedef float Real;
	template <int dims, typename T> class Vector;
	typedef Vector<3, Real> Vector3;
}

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

