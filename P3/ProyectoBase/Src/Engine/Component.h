#pragma once

/*
	This is an abstract superclass from which every 
	engine component or game component should inherit
*/

class Component {
private:
	
	// Whether or not the component should be updated
	bool active_;
	
public:
	Component();
	virtual ~Component();
	
	// Abstract update method for children to implement
	virtual void update() = 0;
	
	// Getters and setters
	bool isActive();
	void setActive(bool active);
	bool toggleActive();
};