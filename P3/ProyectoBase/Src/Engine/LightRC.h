#pragma once

#include "RenderComponent.h"

#include <string>

class LightRC : public RenderComponent 
{
	public:
		LightRC();
		virtual ~LightRC();

		virtual void render();
};

