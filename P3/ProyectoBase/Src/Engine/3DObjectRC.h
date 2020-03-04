#pragma once

#include <string>
#include "RenderComponent.h"

class TridimensionalObject : public RenderComponent {

public:
	TridimensionalObject();
	virtual ~TridimensionalObject();

	virtual void render();
	void setMaterial(std::string material);
};

