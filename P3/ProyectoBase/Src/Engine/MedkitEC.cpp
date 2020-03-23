#include "MedkitEC.h"

#include "Entity.h"
#include "ComponentsManager.h"
#include "FactoriesFactory.h"
#include "OgreVector3.h"
#include "Scene.h"
#include "TransformComponent.h"

#include "Factory.h"
#include <json.h>
#include <iostream>

#include <iostream>

MedkitEC::MedkitEC() {
	//medkitEC = new TransformComponent();
}

MedkitEC::~MedkitEC() {}

void MedkitEC::update() {}

void MedkitEC::setProbability(float _probability) {
    probability = _probability;
}

void MedkitEC::setDuration(float _duration) { duration = _duration; }

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

// FACTORY INFRASTRUCTURE
class MedkitECFactory final : public ComponentFactory {
  public:
    MedkitECFactory() = default;

    Component* create(Entity* _father, Json::Value& _data,
                      Scene* scene) override {
        MedkitEC* medkitEC = new MedkitEC();

        medkitEC->setFather(_father);
        medkitEC->setScene(scene);
        scene->getComponentsManager()->addPC(medkitEC);

        if (!_data["probality"].isDouble())
            throw std::exception("Shield: probality is not a double");
        medkitEC->setProbability(_data["probality"].asDouble());
        if (!_data["time"].isDouble())
            throw std::exception("Shield: time is not a double");
        medkitEC->setDuration(_data["time"].asDouble());

        medkitEC->setActive(true);

        return medkitEC;
    };
};

REGISTER_FACTORY("medkitEC", MedkitEC);
