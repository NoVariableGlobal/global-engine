#include "Component.h"

class GunC : public Component
{
private:
	int bulletchamber; // Ammunition in chamber
	int bulletchamberMax; // Total ammunition in chamber
	int	munition; // Total ammunition stored
	int	cadence; // Gun cadence
	int	damage; // Gun damage by bullet
	bool semiautomatic; // One shot or multiple shot gun

public:
	GunC(int _bulletchamber, int _munition, int _cadence, int _damage, bool _semiautomatic);
	~GunC();

	// Tries to reload the gun, returns false if failed
	bool reload();
	
	// Tries to fire a shot, returns false if gun is empty
	bool shoot();

	// Returns wheter or not there is ammunition left in the gun
	bool mmunitionleft();

	// Getters
	int getbulletchamber();
	int getmunition();
	int getcadence();
	int getdamage();
	bool getsemiautomatic();
};