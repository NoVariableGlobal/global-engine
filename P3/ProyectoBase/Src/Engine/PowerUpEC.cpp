#include "PowerUpEC.h"

#include "OgreRoot.h"

void PowerUpEC::update() {
    if (!picked && timeToDisappear()) {
        // TODO: destroy power up after not being picked and time being done
    } else if (picked) {
		// TODO: destroy power up after time of effect is done
	}
}

bool PowerUpEC::timeToDisappear() {
    float seconds = clock() / static_cast<float>(CLOCKS_PER_SEC);
    if (timeOfEffect + timeBeforeDelete <= seconds) {
        return true;
    } else {
        timeOfEffect = seconds;
    }
    return false;
}

void PowerUpEC::setTimeBeforeDelete(float _timeBeforeDelete) {
    timeBeforeDelete = _timeBeforeDelete;
}

void PowerUpEC::setTimeOfEffect(float _timeOfEffect) {
    timeOfEffect = _timeOfEffect;
}

bool PowerUpEC::isPicked() { return picked; }

void PowerUpEC::setPicked(bool _picked) { picked = _picked; }


/*
,
{
    "id": "MedkitGenerator",
    "components": [
        {
            "type": "TransformComponent",
            "attributes": {
            "position": [ 0, 0, 0 ],
                "orientation": [ 0, 0, 0 ],
                "scale": [ 0.05, 0.05, 0.05 ]
            }
        },
        {
            "type": "TridimensionalObjectRC",
            "attributes": {
            "mesh": "cube.mesh",
                "node": "nCube",
                "material": "GrassMaterial"
            }
        },
        {
            "type": "SpawnerFloorRandomEC",
            "attributes": {
            "spawnCooldown": 10,
                "spawnID": [ "Medkit" ],
                "spawnChances": [ 20 ]
            }
        }
    ]
}
*/