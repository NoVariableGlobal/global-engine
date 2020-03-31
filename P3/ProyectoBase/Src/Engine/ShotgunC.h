#pragma once
#include "GunC.h"
#include <string>

class ShotgunC : public GunC {
  private:
	// Number of pellets each shot fires
    int nPellets;

	// Distance in angles between each pellet
    int dispAngle;

  public:
    ShotgunC();
    ~ShotgunC();

	virtual void destroy();
    virtual bool shoot();

	void setNPellets(int n);
	void setDispersion(int n);
};