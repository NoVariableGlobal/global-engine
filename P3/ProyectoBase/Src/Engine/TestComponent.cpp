#include <json.h>

#include "ComponentsManager.h"
#include "Entity.h"
#include "FactoriesFactory.h"
#include "Factory.h"
#include "Ogre.h"
#include "Scene.h"
#include "TestComponent.h"

TestComponent::TestComponent() { _color = new Ogre::Vector3(); }

TestComponent::~TestComponent() { delete _color; }

void TestComponent::update() {
    // Whatever
}

void TestComponent::setMaterial(std::string material) { _material = material; }

void TestComponent::setColor(Ogre::Vector3 color) { *_color = color; }

std::string TestComponent::getMaterial() { return _material; }

Ogre::Vector3* TestComponent::getColor() { return _color; }

// FACTORY INFRASTRUCTURE
class TestComponentFactory final : public ComponentFactory {
  public:
    TestComponentFactory() = default;

    Component* create(Entity* father, Json::Value& _data,
                      Scene* scene) override {
        TestComponent* testComponent = new TestComponent();
        testComponent->setFather(father);
        testComponent->setScene(scene);
        testComponent->setMaterial(_data["material"].asString());
        testComponent->setColor(Ogre::Vector3(_data["color"][0].asFloat(),
                                              _data["color"][1].asFloat(),
                                              _data["color"][2].asFloat()));

        scene->getComponentsManager()->addPC(testComponent);
        return testComponent;
    };
};

REGISTER_FACTORY("TestComponent", TestComponent);
