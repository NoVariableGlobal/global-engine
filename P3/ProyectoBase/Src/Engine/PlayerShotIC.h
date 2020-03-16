#pragma once

#include "InputComponent.h"

namespace Ogre {
	typedef float Real;
	template <int dims, typename T> class Vector;
	typedef Vector<3, Real> Vector3;
}

class PlayerShotIC : public InputComponent
{
	private:
	public:
		PlayerShotIC();
		virtual ~PlayerShotIC();

		virtual void handleInput(const SDL_Event& _event);
};