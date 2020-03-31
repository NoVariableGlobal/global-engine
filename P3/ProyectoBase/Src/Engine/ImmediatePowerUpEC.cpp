#include "ImmediatePowerUpEC.h"
#include "Scene.h"

void ImmediatePowerUpEC::checkEvent() {
    PowerUpEC::checkEvent();

    // If it was not picked and the power up collided with the player, set
    // picked to true, call abstract onPick, and delete the power-up from the
    // scene.
    if (!getPicked() && getCollisionWithPlayer()) {
        setPicked(true);
        onPick();
        onDestroy();
    }

    // Delete item when the effect has passed
    if (!getPicked() && timeDisappearEffect()) {
        onDestroy();
    }
}
