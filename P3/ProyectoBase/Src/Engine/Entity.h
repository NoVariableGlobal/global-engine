#pragma once
#include <vector>   
#include <string>  
#include <math.h>

namespace Ogre {
	typedef float Real;
	template <int dims, typename T> class Vector;
	typedef Vector<3, Real> Vector3;
}

class Component;

class Entity {
protected:
	// Position of the entity in the 3D world
	Ogre::Vector3* _position = nullptr;
		// Rotation of the entity in the 3 axis
	Ogre::Vector3* _rotation = nullptr;
	// Scale of the entity in the 3 axis
	Ogre::Vector3* _scale = nullptr;

	// ID attached to the entity
	std::string id;
	// List of components attached to the entity
	std::vector<Component*> components;
	
public:
	Entity();
	virtual ~Entity();

	// Adds the component to the entity's list of components and to the Component Manager's
	void addComponent(Component* c);

	// Getters and Setters
	std::string getId();
	void setId(std::string _id);

	Ogre::Vector3 getScale();
	void setScale(Ogre::Vector3 s);

	Ogre::Vector3 getPosition();
	void setPosition(Ogre::Vector3 p);

	Ogre::Vector3 getRotation();
	void setRotation(Ogre::Vector3 r);
};