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
	// speed at which the player moves each frame
	float _speed;
public:
	PlayerMovementIC();
	virtual ~PlayerMovementIC();

	// Updates the entity's transform's 
	// position upon pressing WASD keys
	virtual void handleInput(const SDL_Event& _event);

	// Sets the speed the entity moves at
	void setMovementSpeed(float speed);
};

