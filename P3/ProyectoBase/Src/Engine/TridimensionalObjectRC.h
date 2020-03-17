#pragma once

#include <string>
#include "RenderComponent.h"

class TridimensionalObjectRC : public RenderComponent {

public:
	TridimensionalObjectRC();
	virtual ~TridimensionalObjectRC();

	// Updates the position and scale of the object
	virtual void render();

	// Sets a given material to the object
	void setMaterial(std::string material);
};

