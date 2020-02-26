#pragma

#include "Component.h"
//#include "sdl_includes.h"

#include "Game.h" // ????


class PhysicsComponent : public Component {
public:
	PhysicsComponent();
	virtual ~PhysicsComponent();
	virtual void update() = 0;

};

// PENDING TO REMOVE
/*
class PhysicFactory : public ComponentFactory
{
	public:
		PhysicFactory() {};
		void create(); // No se puede pq PhysicsComponent es abstracto
};

class PhysicFactoryRegister
{
	PhysicFactoryRegister() { factory.insert({ "PhysicsComponent", new PhysicFactory() }); }
};

PhysicFactoryRegister physicFactoryRegister;
*/