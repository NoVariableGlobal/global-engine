#pragma once

#include "RenderComponent.h"
#include "Factory.h"
#include <string>

// FACTORY INFRASTRUCTURE DECLARATION
DECLARE_FACTORY(TridimensionalObjectRC);

class TridimensionalObjectRC : public RenderComponent {

  public:
    TridimensionalObjectRC();
    virtual ~TridimensionalObjectRC();

    virtual void destroy();

    // Updates the position and scale of the object
    virtual void render();

    // Sets a given material to the object
    void setMaterial(std::string material);
};
