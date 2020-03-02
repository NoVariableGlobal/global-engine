#include "Entity.h"
#include"Ogre.h"
#include "OgreVector3.h"


Entity::Entity() {}

Entity::~Entity() {}

void Entity::addComponent(std::string name, Component* c) 
{
	components.insert({ name, c });
	// Registrar componente en el manager
}

Component* Entity::getComponent(std::string name)
{ 
	int a;
	a = 5;
	return components.find(name)->second; 
}

std::string Entity::getId() { return id; }
void Entity::setId(std::string _id) { id = _id; }