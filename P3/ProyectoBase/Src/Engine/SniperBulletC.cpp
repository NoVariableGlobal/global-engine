#include "SniperBulletC.h"
#include "Scene.h"
#include "Factory.h"
#include "ComponentsManager.h"
#include <json.h>
#include "FactoriesFactory.h"

void SniperBulletC::dealCollision() {}

// FACTORY INFRASTRUCTURE
class SniperBulletCFactory final : public ComponentFactory {
  public:
    SniperBulletCFactory() = default;

    Component* create(Entity* _father, Json::Value& _data,
                      Scene* _scene) override {

        SniperBulletC* bullet = new SniperBulletC();
        _scene->getComponentsManager()->addDC(bullet);

        bullet->setFather(_father);
        bullet->setScene(_scene);

        if (!_data["damage"].isDouble())
            throw std::exception("BulletC: damage is not a double");
        bullet->setDamage(_data["damage"].asDouble());

        return bullet;
    };
};

REGISTER_FACTORY("SniperBulletC", SniperBulletC);