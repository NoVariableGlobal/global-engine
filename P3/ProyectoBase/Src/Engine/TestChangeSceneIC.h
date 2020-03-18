#pragma once

#include "InputComponent.h"

namespace Ogre {
	typedef float Real;
	template <int dims, typename T> class Vector;
	typedef Vector<3, Real> Vector3;
}

class TestChangeSceneIC : public InputComponent
{
	private:
	public:
		TestChangeSceneIC();
		virtual ~TestChangeSceneIC();

		// On mouse button down, tells a gun component to fire a shot
		virtual void handleInput(const SDL_Event& _event);
};