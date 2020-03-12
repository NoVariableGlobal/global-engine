#pragma once

#include "Component.h"

namespace Ogre {
	typedef float Real;
	template <int dims, typename T> class Vector;
	typedef Vector<3, Real> Vector3;
}

class LifeComponent : public Component 
{
	private:
		int totalLife;
		float currentLife;

	public:
		LifeComponent();
		virtual ~LifeComponent();

		// get the current life
		float getLife();
		// set the current life
		void setLife(int _life);

		// get the total life
		int getTotalLife();
		// set the total life
		void setTotalLife(int _life);

		// subtract the damage to the life
		void doDamage(float _damage);
		// subtract the damage to the life
		void heal(float _heal);
};