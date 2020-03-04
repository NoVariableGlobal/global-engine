#pragma

#include "Component.h"

class RenderComponent : public Component {
public:
	RenderComponent();
	virtual ~RenderComponent();
	virtual void render() = 0;

};
