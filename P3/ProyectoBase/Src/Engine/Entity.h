#pragma once

#include <vector>
#include <string>

class Component;

class Entity {
protected:
	// Id attached to the entity
	std::string id;
	// List of components attached to the entity
	std::vector<Component*> components;
	// Position of the entity in the 3D world
	//Vector3 position_;
	//
	//// Rotation of the entity in the 3 axis
	//Vector3 rotation_;
	//
	//// Scale of the entity in the 3 axis
	//Vector3 scale_;
	//
	
public:
	Entity();
	virtual ~Entity();

	// Adds the component to the entity's list of components and to the Component Manager's
	void addComponent(Component* _c);

	void addId(std::string _id);
	
	// Getters and Setters
	//Vector3 getScale();
	//void setScale(Vector3 s);

	//Vector3 getPosition();
	//void setPosition(Vector3 p);

	//Vector3 getRotation();
	//void setRotation(Vector3 r);
};