#pragma

//#include "Component.h"
//#include "sdl_includes.h"

class InputComponent {//: virtual public Component {
public:
	InputComponent();
	virtual ~InputComponent();
	virtual void update() = 0;

};
