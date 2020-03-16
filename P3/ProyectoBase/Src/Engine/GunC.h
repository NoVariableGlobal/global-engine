#include "Component.h"

class GunC : public Component
{
private:
	int bulletchamber; //municion en la recamara
	int bulletchamberMax;
	int	munition; //municion total guardada
	int	cadence;
	int	damage;
	bool semiautomatic;
public:
	GunC(int _bulletchamber, int _munition, int _cadence, int _damage, bool _semiautomatic);
	~GunC();
	bool reload();
	bool shoot();
	int getbulletchamber();
	int getmunition();
	int getcadence();
	int getdamage();
	bool getsemiautomatic();
	bool mmunitionleft();
};