#pragma once

#include <string>
#include "RenderComponent.h"

class TridimensionalObjectRC : public RenderComponent {

public:
	TridimensionalObjectRC();
	virtual ~TridimensionalObjectRC();

	virtual void render();
	void setMaterial(std::string material);
};

