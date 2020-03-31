#include "MedkitEC.h"

#include "ComponentsManager.h"
#include "Entity.h"
#include "FactoriesFactory.h"
#include "Factory.h"
#include "LifeC.h"
#include "OgreVector3.h"
#include "Scene.h"
#include "TransformComponent.h"
#include "RigidbodyPC.h"
#include "TridimensionalObjectRC.h"

#include <iostream>
#include <json.h>

MedkitEC::MedkitEC() {}
MedkitEC::~MedkitEC(){}

void MedkitEC::destroy() {
    setActive(false);
    scene->getComponentsManager()->eraseEC(this);
}

void MedkitEC::checkEvent() {
    PowerUpEC::checkEvent();

    if (!picked && getCollisionWithPlayer()) {
        LifeC* playerHealth = dynamic_cast<LifeC*>(
            scene->getEntitybyId("Player")->getComponent("LifeC"));
        playerHealth->heal(playerHealth->getTotalLife());
        picked = true;

        scene->deleteEntity(father);
    }
    if (!picked) { // delete item when the effect has passed
        if (timeDisappear()) {
            // TODO: Delete the entire object
            scene->deleteEntity(father);

            /*RenderComponent* render = dynamic_cast<RenderComponent*>(
                scene->getEntitybyId("Shield0")->getComponent(
                    "TridimensionalObjectRC"));
            compManager->deleteRC(render);
            delete this;*/
        }
    }
}

// FACTORY INFRASTRUCTURE
class MedkitECFactory final : public ComponentFactory {
  public:
    MedkitECFactory() = default;

    Component* create(Entity* _father, Json::Value& _data,
                      Scene* scene) override {
        MedkitEC* medkitEC = new MedkitEC();
        scene->getComponentsManager()->addEC(medkitEC);
        medkitEC->setFather(_father);
        medkitEC->setScene(scene);

        if (!_data["time"].isDouble())
            throw std::exception("Shield: time is not a double");
        medkitEC->setDuration(_data["time"].asDouble());

        medkitEC->setActive(true);

        return medkitEC;
    };
};

REGISTER_FACTORY(MedkitEC);
