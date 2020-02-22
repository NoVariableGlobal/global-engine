#pragma

//#include "Component.h"
//#include "sdl_includes.h"

class PhysicsComponent {//: virtual public Component {
public:
	PhysicsComponent();
	virtual ~PhysicsComponent();
	virtual void update() = 0;

};