#pragma once
#include<map>
#include <string>

namespace Ogre {
	typedef float Real;
	template <int dims, typename T> class Vector;
	typedef Vector<3, Real> Vector3;
}

class Component;

class Entity {
private:

	// ID attached to the entity
	std::string id;
	// List of components attached to the entity
	std::map<std::string, Component*> components;
	
public:
	Entity();
	virtual ~Entity();

	// Adds the component to the entity's list of components and to the Component Manager's
	void addComponent(std::string name, Component* c);
	Component* getComponent(std::string name);

	// Getters and Setters
	std::string getId();
	void setId(std::string _id);
};