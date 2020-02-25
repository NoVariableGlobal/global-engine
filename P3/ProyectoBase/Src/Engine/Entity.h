#pragma once

#include "Component.h"
#include <vector>

class Entity {
protected:
	// Position of the entity in the 3D world
	Vector3 position_;
	
	// Rotation of the entity in the 3 axis
	Vector3 rotation_;
	
	// Scale of the entity in the 3 axis
	Vector3 scale_;
	
	// List of components attached to the entity
	vector<Component*> components;
	
public:
	Entity();
	virtual ~Entity();

	// Adds the component to the entity's list of components and to the Component Manager's
	void addComponent(Component* c);
	
	// Getters and Setters
	Vector3 getScale();
	void setScale(Vector3 s);

	Vector3 getPosition();
	void setPosition(Vector3 p);

	Vector3 getRotation();
	void setRotation(Vector3 r);
};