#pragma once

#include "Component.h"

namespace Ogre {
	typedef float Real;
	template <int dims, typename T> class Vector;
	typedef Vector<3, Real> Vector3;
}

class PlayerShotIC : public Component 
{
	private:
	public:
		PlayerShotIC();
		virtual ~PlayerShotIC();
};