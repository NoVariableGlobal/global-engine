#include "LifeC.h"

#include "ComponentsManager.h"
#include "FactoriesFactory.h"
#include "Factory.h"
#include "OgreRoot.h"
#include "OgreVector3.h"
#include "Scene.h"

#include <json.h>

LifeC::LifeC() {}

LifeC::~LifeC() {}

float LifeC::getLife() { return currentLife; }

void LifeC::setLife(int _life) { currentLife = _life; }

int LifeC::getTotalLife() { return totalLife; }

void LifeC::setTotalLife(int _life) { totalLife = _life; }

void LifeC::doDamage(float _damage) {
    currentLife -= _damage;

    if (currentLife < 0)
        currentLife = 0;
}

void LifeC::heal(float _heal) {
    currentLife += _heal;

    if (currentLife > totalLife)
        currentLife = totalLife;
}

// FACTORY INFRASTRUCTURE
class LifeCFactory : public ComponentFactory {
  public:
    LifeCFactory(){};
    virtual Component* create(Entity* _father, Json::Value& _data,
                              Scene* scene) {
        LifeC* life = new LifeC();

        life->setFather(_father);

        if (!_data["life"].isInt()) { /*EXCEPCION*/
        }
        life->setTotalLife(_data["life"].asInt());
        life->setLife(_data["life"].asInt());

        scene->getComponentsManager()->addDC(life);
        return life;
    };
};

REGISTER_FACTORY("LifeC", LifeC);
