#include "MedkitEC.h"
#include <iostream>

MedkitEC::MedkitEC() {
	medkitEC = new TransformComponent();
}

MedkitEC::~MedkitEC() { delete medkitEC; }

void MedkitEC::onCollisionActivate() {
    if (checkCollision()) {
        //player.setTotalLife(player.life);
        std::cout << "Health restored to full\n";
	}
    delete this;
}

bool MedkitEC::checkCollision() {
    // if (checkCollision(player)) { return true; }
	return true;
}
