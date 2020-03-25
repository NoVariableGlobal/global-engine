#include "LifeC.h"

#include "ComponentsManager.h"
#include "FactoriesFactory.h"
#include "Factory.h"
#include "OgreRoot.h"
#include "Scene.h"

#include <json.h>

LifeC::LifeC(): invulnerability(false) {}

LifeC::~LifeC() {}

void LifeC::destroy() {
    setActive(false);
    scene->getComponentsManager()->eraseDC(this);
}


float LifeC::getLife() { return currentLife; }

void LifeC::setLife(int _life) { currentLife = _life; }

int LifeC::getTotalLife() { return totalLife; }

void LifeC::setTotalLife(int _life) { totalLife = _life; }

void LifeC::doDamage(float _damage) {
    if (!invulnerability)
		currentLife -= _damage;

    if (currentLife < 0)
        currentLife = 0;
}

void LifeC::heal(float _heal) {
    currentLife += _heal;

    if (currentLife > totalLife)
        currentLife = totalLife;
}

void LifeC::setInvulnerability(bool _invulnerability) {
    invulnerability = _invulnerability;
}

// FACTORY INFRASTRUCTURE
class LifeCFactory : public ComponentFactory {
  public:
    LifeCFactory(){};
    virtual Component* create(Entity* _father, Json::Value& _data,
                              Scene* _scene) {
        LifeC* life = new LifeC();
        _scene->getComponentsManager()->addDC(life);

        life->setFather(_father);
        life->setScene(_scene);

        if (!_data["life"].isInt()) { /*EXCEPCION*/
        }
        life->setTotalLife(_data["life"].asInt());
        life->setLife(_data["life"].asInt());

        return life;
    };
};

REGISTER_FACTORY("LifeC", LifeC);
