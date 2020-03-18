#pragma once

#include "InputComponent.h"

#include <string>

namespace Ogre {
	typedef float Real;
	template <int dims, typename T> class Vector;
	typedef Vector<3, Real> Vector3;
}

class TestChangeSceneIC : public InputComponent
{
	private:
		std::string sceneToChange;

	public:
		TestChangeSceneIC();
		virtual ~TestChangeSceneIC();

		void setSceneToChange(std::string scene);

		// On mouse button down, tells a gun component to fire a shot
		virtual void handleInput(const SDL_Event& _event);
};