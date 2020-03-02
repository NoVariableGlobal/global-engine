#pragma

//#include "Component.h"
//#include "sdl_includes.h"

class RenderComponent {//: virtual public Component {
public:
	RenderComponent();
	virtual ~RenderComponent();
	virtual void render() = 0;

};
