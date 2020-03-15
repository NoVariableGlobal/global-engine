#include "Entity.h"


Entity::Entity() {}

Entity::~Entity() 
{
	delete getComponent("TransformComponent");
}

void Entity::addComponent(std::string name, Component* c) 
{
	components.insert({ name, c });
	// Registrar componente en el manager
}


Component* Entity::getComponent(std::string name){ return components.find(name)->second;}

std::string Entity::getId() { return id; }
void Entity::setId(std::string _id) { id = _id; }