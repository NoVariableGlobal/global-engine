#pragma once

#include "Component.h"
#include <vector>   
#include <math.h>

namespace Ogre {
	typedef float Real;
	template <int dims, typename T> class Vector;
	typedef Vector<3, Real> Vector3;
}

class Entity {
protected:
	// Position of the entity in the 3D world
	Ogre::Vector3* _position;
		// Rotation of the entity in the 3 axis
	Ogre::Vector3* _rotation;
	
	// Scale of the entity in the 3 axis
	Ogre::Vector3* _scale;
	
	// List of components attached to the entity
	std::vector<Component*> components;
	
public:
	Entity();
	virtual ~Entity();

	// Adds the component to the entity's list of components and to the Component Manager's
	void addComponent(Component* c);
	
	// Getters and Setters
	Ogre::Vector3 getScale();
	void setScale(Ogre::Vector3 s);

	Ogre::Vector3 getPosition();
	void setPosition(Ogre::Vector3 p);

	Ogre::Vector3 getRotation();
	void setRotation(Ogre::Vector3 r);
};