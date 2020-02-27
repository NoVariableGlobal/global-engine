#pragma

//#include "Component.h"
//#include "sdl_includes.h"

class InputComponent {//: virtual public Component {
public:
	InputComponent();
	virtual ~InputComponent();
	virtual void handleInput() = 0;

};
