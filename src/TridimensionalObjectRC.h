#pragma once

#include "Factory.h"
#include "RenderComponent.h"
#include <string>

// FACTORY INFRASTRUCTURE DECLARATION
DECLARE_FACTORY(TridimensionalObjectRC);

class TridimensionalObjectRC : public RenderComponent {

  public:
    TridimensionalObjectRC();
    virtual ~TridimensionalObjectRC();

    // Updates the position and scale of the object
    virtual void render();

    // Sets a given material to the object
    void setMaterial(std::string material);
    void setRotation(Ogre::Vector3 r);
    void resetRotation();
};
