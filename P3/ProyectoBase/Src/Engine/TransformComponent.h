#pragma once

#include "Component.h"

namespace Ogre {
	typedef float Real;
	template <int dims, typename T> class Vector;
	typedef Vector<3, Real> Vector3;
}

class TransformComponent : public Component 
{
private:
	// Position of the entity in the 3D world
	Ogre::Vector3* _position = nullptr;
	// Rotation of the entity in the 3 axis
	Ogre::Vector3* _orientation = nullptr;
	// Scale of the entity in the 3 axis
	Ogre::Vector3* _scale = nullptr;
public:
	TransformComponent();
	virtual ~TransformComponent();

	// Getters and setters
	Ogre::Vector3 getPosition();
	void setPosition(Ogre::Vector3 p);

	Ogre::Vector3 getOrientation();
	void setOrientation(Ogre::Vector3 r);

	Ogre::Vector3 getScale();
	void setScale(Ogre::Vector3 s);
};