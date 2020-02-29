#include "Entity.h"
#include"Ogre.h"
#include "OgreVector3.h"


Entity::Entity() 
{
	_position = new Ogre::Vector3();
	_scale = new Ogre::Vector3();
	_rotation = new Ogre::Vector3();
}

Entity::~Entity() {}

void Entity::addComponent(Component* c) {
	components.push_back(c);
	// Registrar componente en el manager
}

std::string Entity::getId() { return id; }
void Entity::setId(std::string _id) { id = _id; }

Ogre::Vector3 Entity::getScale() { return *_scale; }
void Entity::setScale(Ogre::Vector3 s) { *_scale = s; }

Ogre::Vector3 Entity::getPosition() { return *_position; }
void Entity::setPosition(Ogre::Vector3 p) { *_position = p; }

Ogre::Vector3 Entity::getRotation() { return *_rotation; }
void Entity::setRotation(Ogre::Vector3 r) { *_rotation = r; }